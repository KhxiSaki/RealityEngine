import os
from pathlib import Path
from Core import Logger
import BuildConfig as Config

def validate() -> bool:
    """Check if shaders need compilation and compile them."""
    Logger.subheader("Shader Compilation")
    
    shader_dir = Path("Engine/Shaders")
    output_dir = Path("Engine/Shaders")
    
    # Check if shader source directory exists
    if not shader_dir.exists():
        Logger.warning("No Engine/Shaders directory found - skipping shader compilation")
        return True
    
    # Find shader files
    shader_files = []
    for ext in [".vert", ".frag", ".comp", ".geom", ".tesc", ".tese"]:
        shader_files.extend(shader_dir.glob(f"*{ext}"))
    
    if not shader_files:
        Logger.info("No shader files found - skipping compilation")
        return True
    
    # Check if output directory exists and has compiled shaders
    needs_compilation = False
    if not output_dir.exists():
        needs_compilation = True
    else:
        # Check if any source shader is newer than compiled version
        for shader_file in shader_files:
            output_file = output_dir / f"{shader_file.stem}.spv"
            if not output_file.exists():
                needs_compilation = True
                break
            if shader_file.stat().st_mtime > output_file.stat().st_mtime:
                needs_compilation = True
                break
    
    if not needs_compilation:
        Logger.success(f"Shaders up to date ({len(shader_files)} shader(s))")
        return True
    
    # Compile shaders
    Logger.info(f"Compiling {len(shader_files)} shader(s)...")
    import subprocess
    result = subprocess.run(["python", "Engine/Build/Modules/CompileShaders.py"], 
                          capture_output=True, text=True)
    
    if result.returncode == 0:
        Logger.success("Shaders compiled successfully")
        return True
    else:
        Logger.error("Shader compilation failed")
        if result.stderr:
            print(result.stderr)
        return False