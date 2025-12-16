import os
import sys
import subprocess
from pathlib import Path

# Fix Windows console encoding
if sys.platform == "win32":
    try:
        sys.stdout.reconfigure(encoding='utf-8')
    except:
        pass

def find_glslc():
    """Find glslc compiler in Vulkan SDK."""
    vulkan_sdk = os.environ.get("VULKAN_SDK")
    if not vulkan_sdk:
        print("ERROR: VULKAN_SDK environment variable not set!")
        return None
    
    glslc_path = Path(vulkan_sdk) / "Bin" / "glslc.exe"
    if not glslc_path.exists():
        print(f"ERROR: glslc.exe not found at {glslc_path}")
        return None
    
    return str(glslc_path)

def compile_shader(glslc, shader_path, output_path):
    """Compile a single shader file."""
    try:
        cmd = [glslc, str(shader_path), "-o", str(output_path)]
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        if result.returncode != 0:
            print(f"  [X] Failed to compile {shader_path.name}")
            print(f"      {result.stderr}")
            return False
        
        print(f"  [OK] Compiled {shader_path.name} -> {output_path.name}")
        return True
    except Exception as e:
        print(f"  [X] Error compiling {shader_path.name}: {e}")
        return False

def main():
    print("=" * 60)
    print("  Shader Compilation")
    print("=" * 60)
    
    # Find glslc compiler
    glslc = find_glslc()
    if not glslc:
        return 1
    
    # Define shader directories
    shader_dir = Path("Engine/Shaders")
    output_dir = Path("Engine/Binaries/Shaders")
    
    # Create output directory
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Find all shader files
    shader_files = []
    for ext in [".vert", ".frag", ".comp", ".geom", ".tesc", ".tese"]:
        shader_files.extend(shader_dir.glob(f"*{ext}"))
    
    if not shader_files:
        print("\n[!] No shader files found in Engine/Shaders/")
        return 0
    
    print(f"\nFound {len(shader_files)} shader(s) to compile:\n")
    
    # Compile each shader
    success_count = 0
    for shader_path in shader_files:
        # Output file naming:
        # shader.vert -> shader.spv
        # shader.frag -> frag.spv
        # myshader.comp -> myshader.spv
        if shader_path.suffix == ".frag":
            # Special case for fragment shaders to match engine expectations
            output_name = "frag.spv"
        else:
            output_name = shader_path.stem + ".spv"
        
        output_path = output_dir / output_name
        
        if compile_shader(glslc, shader_path, output_path):
            success_count += 1
    
    # Summary
    print("\n" + "=" * 60)
    if success_count == len(shader_files):
        print(f"  [OK] Successfully compiled all {success_count} shader(s)")
    else:
        print(f"  [!] Compiled {success_count}/{len(shader_files)} shader(s)")
    print("=" * 60 + "\n")
    
    return 0 if success_count == len(shader_files) else 1

if __name__ == "__main__":
    sys.exit(main())