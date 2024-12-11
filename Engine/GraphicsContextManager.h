#pragma once
#include "GraphicsInterface.h"

class GraphicsContext {
public:
    static GraphicsContext& GetInstance() {
        static GraphicsContext instance;
        return instance;
    }

    void SetGraphicsAPI(IGraphicsAPI* api) {
        if (currentAPI) {
            currentAPI->Shutdown();
        }
        currentAPI = api;
        currentAPI->Initialize();
    }

    IGraphicsAPI* GetCurrentAPI() {
        return currentAPI;
    }

private:
    IGraphicsAPI* currentAPI = nullptr;
};