//
// Created by HongZh on 2022/05/06, 15:04:04
//

#ifndef ALICE_ENGINE_RENDER_ENGINE
#define ALICE_ENGINE_RENDER_ENGINE

#include "RenderModules/initialization_mod.h"
#include "render_task.h"
#include <mutex>

namespace AliceAPI {

class RenderEngine{
public:
    void initEngine(); // initialize the render engine 
    void doRender(std::shared_ptr<RenderTask> task);  // 

    RenderEngine();
    ~RenderEngine();
private:
    std::mutex mtx_;
    void render(std::shared_ptr<RenderTask> task);
    void preRender(std::shared_ptr<RenderTask> task);
    void postRender(std::shared_ptr<RenderTask> task);
};

}

#endif //ALICE_ENGINE_RENDER_ENGINE