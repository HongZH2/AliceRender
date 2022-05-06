//
// Created by HongZh on 2022/05/06, 15:09:53
//

#include "render_engine.h"

namespace AliceAPI {

RenderEngine::RenderEngine(){

}

RenderEngine::~RenderEngine(){

}

void RenderEngine::initEngine(){
    auto & initHander = InitModule::getInstancePtr();
}



void RenderEngine::preRender(std::shared_ptr<RenderTask> task){
    std::lock_guard<std::mutex> lock(mtx_);
     // fbo
    task->bindFBO();
    // status 
    task->applyStatus();
}

void RenderEngine::postRender(std::shared_ptr<RenderTask> task){
    std::lock_guard<std::mutex> lock(mtx_);
    // reset status
    task->resetStatus();   
    // reset fbo
    task->unbindFBO();
}

void RenderEngine::render(std::shared_ptr<RenderTask> task){
     std::lock_guard<std::mutex> lock(mtx_);
    // fbo
    task->bindFBO();
    // status 
    task->applyStatus();
    // shader
    task->bindShader();
    // texture
    task->bindTexture();
    // attribute
    task->updateAttribute();
    //param
    task->updateParams();
    // VBO
    task->bindDataModule();
    // draw element
    task->draw();
    // data mod
    task->unbindDataModule();
    // texture
    task->unbindTexture();
    // shader
    task->unbindShader();
    // status
    task->resetStatus();   
    // fbo
    task->unbindFBO();
}



void RenderEngine::doRender(std::shared_ptr<RenderTask> task){
    // start rendering
    switch(task->getRenderDataType()){
        case PRE_RENDER_TASK:{
            preRender(task);
            break;
        }
        case RENDERABLE_TASK:{
            render(task);
            break;
        }
        case POST_RENDER_TASK:{
            postRender(task);
            break;
        }
    }
}

}