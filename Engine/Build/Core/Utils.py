import os
import sys
import time
import shutil
from pathlib import Path
from zipfile import ZipFile
from typing import Optional

def ensure_directory(path: str) -> Path:
    """Create directory if it doesn't exist."""
    p = Path(path)
    p.mkdir(parents=True, exist_ok=True)
    return p

def download_file(url: str, filepath: str, show_progress: bool = True) -> bool:
    """Download a file from URL with progress bar."""
    import requests
    
    filepath = os.path.abspath(filepath)
    ensure_directory(os.path.dirname(filepath))
    
    try:
        headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'}
        response = requests.get(url, headers=headers, stream=True, timeout=30)
        response.raise_for_status()
        
        total = response.headers.get('content-length')
        
        with open(filepath, 'wb') as f:
            if total is None or not show_progress:
                f.write(response.content)
            else:
                downloaded = 0
                total = int(total)
                start_time = time.time()
                
                for data in response.iter_content(chunk_size=1024 * 1024):
                    downloaded += len(data)
                    f.write(data)
                    _print_progress(downloaded, total, start_time)
                    
        if show_progress and total:
            sys.stdout.write('\n')
        return True
        
    except Exception as e:
        print(f"\n  Error downloading: {e}")
        if os.path.exists(filepath):
            os.remove(filepath)
        return False

def extract_zip(filepath: str, delete_after: bool = True, show_progress: bool = True) -> bool:
    """Extract a zip file with progress bar."""
    filepath = os.path.abspath(filepath)
    extract_dir = os.path.dirname(filepath)
    
    try:
        with ZipFile(filepath, 'r') as zf:
            members = zf.namelist()
            total_size = sum(zf.getinfo(m).file_size for m in members)
            extracted_size = 0
            start_time = time.time()
            
            for member in members:
                zf.extract(member, extract_dir)
                extracted_size += zf.getinfo(member).file_size
                if show_progress and total_size > 0:
                    _print_progress(extracted_size, total_size, start_time)
                    
        if show_progress:
            sys.stdout.write('\n')
            
        if delete_after:
            os.remove(filepath)
        return True
        
    except Exception as e:
        print(f"\n  Error extracting: {e}")
        return False

def _print_progress(current: int, total: int, start_time: float) -> None:
    """Print a progress bar."""
    done = int(50 * current / total) if current < total else 50
    pct = (current / total) * 100 if current < total else 100
    elapsed = time.time() - start_time
    
    speed = (current / 1024) / elapsed if elapsed > 0 else 0
    speed_str = f"{speed:.1f} KB/s" if speed < 1024 else f"{speed/1024:.1f} MB/s"
    
    sys.stdout.write(f'\r  [{"█" * done}{"·" * (50-done)}] {pct:.1f}% ({speed_str})  ')
    sys.stdout.flush()

def prompt_yes_no(message: str) -> bool:
    """Prompt user for yes/no input."""
    while True:
        reply = input(f"  {message} [Y/N]: ").lower().strip()
        if reply in ('y', 'yes'):
            return True
        if reply in ('n', 'no'):
            return False