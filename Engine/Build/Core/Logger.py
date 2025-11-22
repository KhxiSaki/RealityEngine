import sys

class Colors:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    RESET = '\033[0m'
    BOLD = '\033[1m'

def _supports_color() -> bool:
    return sys.platform == "win32" or hasattr(sys.stdout, 'isatty') and sys.stdout.isatty()

_use_color = _supports_color()

def _colored(text: str, color: str) -> str:
    return f"{color}{text}{Colors.RESET}" if _use_color else text

def info(msg: str) -> None:
    print(f"  {msg}")

def success(msg: str) -> None:
    print(_colored(f"  ✓ {msg}", Colors.GREEN))

def warning(msg: str) -> None:
    print(_colored(f"  ⚠ {msg}", Colors.YELLOW))

def error(msg: str) -> None:
    print(_colored(f"  ✗ {msg}", Colors.RED))

def header(msg: str) -> None:
    print()
    print(_colored(f"{'='*60}", Colors.CYAN))
    print(_colored(f"  {msg}", Colors.CYAN + Colors.BOLD))
    print(_colored(f"{'='*60}", Colors.CYAN))

def subheader(msg: str) -> None:
    print()
    print(_colored(f"── {msg} ──", Colors.BLUE))