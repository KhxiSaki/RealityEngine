#pragma once

struct TextureDesc {
    int width;
    int height;
    int format; // e.g., RGBA, RGB, etc.
    void* data; // Pointer to texture data
};

struct BufferDesc {
    int size;
    void* data; // Pointer to buffer data
    int usage;  // e.g., Vertex Buffer, Index Buffer, etc.
};

struct ShaderDesc {
    const char* source; // Shader source code
    int type;           // e.g., Vertex Shader, Fragment Shader, etc.
};

struct PipelineDesc {
    // Define pipeline state settings
    // e.g., shaders, blend state, rasterizer state, etc.
};

struct DrawCommand {
    int vertexCount; // Number of vertices to draw
    int instanceCount; // Number of instances to draw
    int firstVertex; // Starting vertex index
    int firstInstance; // Starting instance index
    // Add other necessary fields (e.g., index buffer, texture ID, etc.)
};