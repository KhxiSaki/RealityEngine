@echo off
echo Compiling shaders...

set VULKAN_SDK=C:\VulkanSDK\1.4.335.0

"%VULKAN_SDK%\Bin\glslc.exe" Engine/Shaders/shader.vert -o Engine/Shaders/vert.spv
"%VULKAN_SDK%\Bin\glslc.exe" Engine/Shaders/shader.frag -o Engine/Shaders/frag.spv

echo Done!
pause
