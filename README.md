# RealityEngine

Welcome to the RealityEngine source code!

RealityEngine is a modern C++23 game engine built with Vulkan, featuring an ImGui-based editor interface. With this codebase, you can build the engine, create games, and extend the functionality to suit your needs.

## System Requirements

### Windows
- **Operating System**: Windows 10/11 (64-bit)
- **IDE**: Visual Studio 2022 (Community, Professional, or Enterprise)
- **Python**: Python 3.14 or later
- **Git**: Git for Windows (for dependency management)
- **Vulkan SDK**: Version 1.4.309.0 or later
- **Disk Space**: ~5 GB for engine and dependencies

### Supported Platforms
Currently, RealityEngine targets Windows 64-bit systems. Future support for additional platforms may be added.

## Getting Started

The steps below will guide you through setting up RealityEngine on your system.

### Step 1: Install Prerequisites

#### Install Python
1. Download Python 3.14 or later from [python.org](https://www.python.org/downloads/)
2. During installation, **make sure to check "Add Python to PATH"**
3. Verify installation by opening a command prompt and typing:
   ```
   python --version
   ```
   You should see `Python 3.14.x` or later.

#### Install Git
1. Download Git for Windows from [git-scm.com](https://git-scm.com/download/win)
2. Run the installer with default settings
3. Verify installation by opening a command prompt and typing:
   ```
   git --version
   ```
   You should see `git version x.x.x`.

#### Install Visual Studio 2022
1. Download Visual Studio 2022 from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/)
   - The free **Community** edition works perfectly for RealityEngine development
2. During installation, select the **Desktop development with C++** workload
3. Make sure the following components are selected:
   - MSVC v143 or later C++ build tools
   - Windows 10/11 SDK
   - C++ CMake tools (optional but recommended)

### Step 2: Get the Source Code

#### Option A: Using Git (Recommended)
```bash
git clone https://github.com/yourusername/RealityEngine.git
cd RealityEngine
```

#### Option B: Download ZIP
1. Click the **Code** button at the top of this repository
2. Select **Download ZIP**
3. Extract the archive to your desired location
4. **Important**: Right-click the extracted folder, select **Properties**, and click **Unblock** if the option appears

### Step 3: Run the Setup Script

1. Navigate to the RealityEngine root directory in File Explorer
2. **Double-click `Setup.bat`** to begin the setup process

The setup script will:
- ✅ Check your Python version and install required packages
- ✅ Download and install Premake (build system generator)
- ✅ Download third-party dependencies (ImGui, etc.)
- ✅ Check for Vulkan SDK installation
- ✅ Initialize Git submodules
- ✅ Generate Visual Studio project files

#### First-Time Vulkan SDK Installation

If you don't have the Vulkan SDK installed, the setup script will detect this and offer to download it for you:

1. When prompted `Download Vulkan SDK 1.4.309.0? [Y/N]:`, type `Y` and press Enter
2. Wait for the download to complete (~150 MB)
3. The **Vulkan SDK installer will launch automatically**
4. During the Vulkan installation:
   - Accept the license agreement
   - Choose the default installation location: `C:\VulkanSDK\1.4.309.0`
   - **Important**: Make sure to check **"Shader Toolchain Debug Symbols"** for debug build support
   - Complete the installation
5. **After Vulkan installation completes**, close any remaining installer windows
6. **Re-run `Setup.bat`** to complete the setup process

#### Expected Output (Successful Setup)

After running Setup.bat successfully, you should see:

```
============================================================
  RealityEngine Setup
============================================================

── Python Environment ──
  Python 3.14.2 detected
  ✓ Python version OK
  ✓ Package 'requests' found

── Third-Party Dependencies ──
  ✓ ImGui (1.91.9b) found

── Premake ──
  ✓ Premake found at ./Engine/Binaries/Premake

── Vulkan SDK ──
  ✓ Vulkan SDK found at C:\VulkanSDK\1.4.309.0
  ✓ Debug libraries found

── Git Submodules ──
  Updating submodules...
  ✓ Submodules updated

── Project Generation ──
  Generating Visual Studio solution...
Building configurations...
Running action 'vs2022'...
Generated RealityEngine.sln...
Done (22ms).
  ✓ Project files generated!

============================================================
  Setup Complete!
============================================================
```

**Note**: If you see `⚠ Debug libs not found`, your debug builds may not work properly. To fix this, re-install the Vulkan SDK and ensure "Shader Toolchain Debug Symbols" is checked.

### Step 4: Build the Engine

1. In the RealityEngine root directory, **double-click `RealityEngine.sln`** to open the solution in Visual Studio 2022

2. In Visual Studio:
   - Set the **Solution Configuration** to `Debug` or `Release` (top toolbar)
   - Set the **Solution Platform** to `x64` (top toolbar)
   - In the **Solution Explorer**, right-click on **RealityEngine** project
   - Select **Set as Startup Project**
   - Press **F7** or select **Build > Build Solution**

3. The first build will take **5-15 minutes** depending on your system

   *Tip: Subsequent builds will be much faster as only changed files are recompiled*

### Step 5: Run the Engine

Once compilation finishes:
- Press **F5** to run with debugging, or **Ctrl+F5** to run without debugging
- The RealityEngine editor window should appear

## Project Structure

```
RealityEngine/
├── Engine/                     # Engine source code
│   ├── Source/
│   │   └── Runtime/           # Core engine runtime
│   ├── ThirdParty/            # Third-party libraries (ImGui, etc.)
│   ├── Binaries/              # Compiled binaries
│   └── Build/                 # Build scripts and configuration
│       ├── Setup.py           # Main setup script
│       ├── GenerateProjectFiles.py
│       └── Modules/           # Setup modules
├── EOC/                       # Example project
│   └── Source/                # Game/application source
├── Setup.bat                  # Windows setup script
├── GenerateVisualStudioFiles.bat
└── premake5.lua              # Build configuration
```

## Regenerating Project Files

If you modify any `.lua` build configuration files or add new source files, you may need to regenerate the Visual Studio project files:

1. **Close Visual Studio** if it's open
2. Run `GenerateVisualStudioFiles.bat`
3. Reopen `RealityEngine.sln`

## Troubleshooting

### "Python is not installed or not in PATH"
- Reinstall Python and ensure "Add Python to PATH" is checked during installation
- Restart your command prompt or computer after installation

### "Git not found in PATH - skipping submodules"
- Install Git from [git-scm.com](https://git-scm.com/download/win)
- Restart your command prompt after installation
- Re-run `Setup.bat`

### "Premake not found! Run Setup.bat first"
- Run `Setup.bat` before trying to generate project files
- If the problem persists, delete the `Engine/Binaries/Premake` folder and re-run `Setup.bat`

### "Vulkan SDK not found in environment"
- Make sure the Vulkan SDK installer completed successfully
- **Restart your computer** after installing the Vulkan SDK
- Verify the `VULKAN_SDK` environment variable is set:
  - Open Command Prompt and type: `echo %VULKAN_SDK%`
  - Should display: `C:\VulkanSDK\1.4.309.0` (or similar)
- Re-run `Setup.bat`

### Visual Studio build errors
- Make sure you're using **Visual Studio 2022** (not 2019 or earlier)
- Verify your solution configuration is set to **x64** (not x86)
- Try **Clean Solution** then **Rebuild Solution**
- Check that all prerequisites are properly installed

### "Cannot import name 'SetupPremake' from 'Modules'"
- This means the `__init__.py` files are missing from the build system
- Download the fixed build system files from the repository
- Make sure these files exist:
  - `Engine/Build/Core/__init__.py`
  - `Engine/Build/Modules/__init__.py`

## Development Workflow

1. **Make changes** to source code in Visual Studio
2. **Build** with F7 (or Build > Build Solution)
3. **Run** with F5 to test your changes
4. **Debug** using Visual Studio's debugging tools (breakpoints, watch windows, etc.)

## Adding Third-Party Dependencies

To add new third-party libraries:

1. Edit `Engine/Build/BuildConfig.py`
2. Add a new `Dependency` entry to the `DEPENDENCIES` list:
   ```python
   Dependency(
       name="YourLib",
       version="1.0.0",
       url="https://github.com/user/lib/archive/v1.0.0.zip",
       install_path=f"{THIRD_PARTY_DIR}/YourLib",
       extracted_folder="lib-1.0.0"  # Folder name in the zip
   )
   ```
3. Run `Setup.bat` to download and install the dependency
4. Update `premake5.lua` to include the library in your build

## Contributing

We welcome contributions to RealityEngine! Here's how you can help:

1. **Fork** the repository
2. **Create a feature branch**: `git checkout -b feature/amazing-feature`
3. **Commit your changes**: `git commit -m 'Add amazing feature'`
4. **Push to the branch**: `git push origin feature/amazing-feature`
5. **Open a Pull Request**

Please ensure your code:
- Follows the existing code style
- Compiles without warnings
- Includes comments for complex logic
- Has been tested on Windows

## License

[Your license information here]

## Additional Resources

- **Documentation**: [Link to your documentation]
- **Community Forum**: [Link to your forum/Discord]
- **Issue Tracker**: Use GitHub Issues to report bugs or request features

## Acknowledgments

RealityEngine uses the following open-source libraries:
- **Dear ImGui** - Bloat-free immediate mode GUI library
- **Vulkan SDK** - Cross-platform graphics and compute API
- **Premake** - Build configuration tool

## Contact

For questions, suggestions, or support:
- Open an issue on GitHub
- [Your contact information]

---

**Happy coding!** 🚀
