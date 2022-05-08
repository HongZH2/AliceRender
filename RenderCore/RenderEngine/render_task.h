//
// Created by zhanghong50 on 2022/1/31.
//

#ifndef ALICEENGINE_RENDER_DATA_H
#define ALICEENGINE_RENDER_DATA_H

#include "RenderModules/fbo_mod.h"
#include "RenderModules/texture_mod.h"
#include "RenderModules/data_mod.h"
#include "RenderModules/draw_mod.h"
#include "RenderModules/shader_mod.h"
#include "RenderModules/status_mod.h"
#include "RenderElement/render_parameter.h"

namespace AliceAPI {

enum RenderTaskType{
    PRE_RENDER_TASK = 0,   // set some common status, like fbo, depth test and so on.. 
    RENDERABLE_TASK = 1,  // it is optional to set/reset status 
    POST_RENDER_TASK = 2,  // reset fbo/status
};

class RenderTask {
public:
    RenderTask();
    ~RenderTask();

    void setFBO(std::shared_ptr<FBOModule> fbo);
    void setStatusModule(std::shared_ptr<StatusSaver> status);
    void setDataModule(std::shared_ptr<DataModule> data);
    void setTexture(std::shared_ptr<TextureModule> texture);
    void setDrawCall(std::shared_ptr<DrawModule> draw);
    void setShaderProgram(std::shared_ptr<ShaderModule> shader_program);
    void setRenderParam(std::shared_ptr<RenderParam> param);
    void setRenderDataType(const RenderTaskType & data_type);

    const RenderTaskType & getRenderDataType();
    std::shared_ptr<DataModule> getDataModule();
    std::shared_ptr<DrawModule> getDrawCall();
    std::shared_ptr<ShaderModule> getShaderProgram();
    std::shared_ptr<RenderParam> getRenderParam();

    void applyStatus();
    void resetStatus();
    void bindFBO();
    void unbindFBO();
    void bindDataModule();
    void unbindDataModule();
    void bindShader();
    void unbindShader();
    void bindTexture();
    void unbindTexture();
    void updateAttribute();
    void updateParams();
    void draw();
    bool isReady();

private:
    std::shared_ptr<StatusSaver> status_; // status module. it could be nullptr
    std::shared_ptr<FBOModule> fbo_;  // fbo , if it is nullptr, the default fbo will be used 
    std::shared_ptr<ShaderModule> shader_program_; // shader
    std::shared_ptr<DataModule> data_;    // Data: VAO,VBO,EBO
    std::shared_ptr<DrawModule> draw_call_;    // draw call
    std::shared_ptr<RenderParam> render_params_;    // render params: uniform variables
    
    RenderTaskType data_type_ = RENDERABLE_TASK;
};

}



#endif //ALICEENGINE_RENDER_DATA_H
