@echo off
echo Compiling shaders...

set VULKAN_SDK=C:\VulkanSDK\1.4.309.0

"%VULKAN_SDK%\Bin\glslc.exe" shader.vert -o vert.spv
"%VULKAN_SDK%\Bin\glslc.exe" shader.frag -o frag.spv

echo Done!
pause
