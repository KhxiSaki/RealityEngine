#pragma once

#include "GraphicsDescriptor.h"

class IGraphicsAPI {
public:
    virtual ~IGraphicsAPI() {}

    // Initialization and shutdown
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    // Frame management
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    // Resource management
    virtual void CreateTexture(const TextureDesc& desc) = 0;
    virtual void CreateBuffer(const BufferDesc& desc) = 0;
    virtual void CreateShader(const ShaderDesc& desc) = 0;
    virtual void CreatePipeline(const PipelineDesc& desc) = 0;

    // Drawing commands
    virtual void Draw(const DrawCommand& command) = 0;

    // State management
    virtual void SetViewport(int x, int y, int width, int height) = 0;
    virtual void SetScissor(int x, int y, int width, int height) = 0;

    // Other necessary methods...
};