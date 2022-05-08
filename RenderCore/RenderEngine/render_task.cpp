//
// Created by zhanghong50 on 2022/1/31.
//

#include "render_task.h"
#include "ElementPool/texture_pool.h"

namespace AliceAPI {


RenderTask::RenderTask() {

}

RenderTask::~RenderTask() {

}

void RenderTask::setStatusModule(std::shared_ptr<StatusSaver> status){
    status_ = status;
}

void RenderTask::setDrawCall(std::shared_ptr<DrawModule> draw) {
    draw_call_ = draw;
}


void RenderTask::setFBO(std::shared_ptr<FBOModule> fbo){
    fbo_ = fbo;
}

void RenderTask::setDataModule(std::shared_ptr<DataModule> data) {
    data_ = data;
}

void RenderTask::setShaderProgram(std::shared_ptr<ShaderModule> shader_program) {
    shader_program_ = shader_program;
}

void RenderTask::setRenderParam(std::shared_ptr<RenderParam> param) {
    render_params_ = param;
}

void RenderTask::setRenderDataType(const RenderTaskType & data_type){
    data_type_ = data_type;
}

const RenderTaskType & RenderTask::getRenderDataType(){
    return data_type_;
}

std::shared_ptr<DataModule> RenderTask::getDataModule() {
    return data_;
}


std::shared_ptr<DrawModule> RenderTask::getDrawCall() {
    return draw_call_;
}

std::shared_ptr<ShaderModule> RenderTask::getShaderProgram() {
    return shader_program_;
}

std::shared_ptr<RenderParam> RenderTask::getRenderParam() {
    return render_params_;
}

void RenderTask::draw(){
    if(draw_call_)
        draw_call_->draw();
}

void RenderTask::bindShader(){
    if(shader_program_)
        shader_program_->bindProgram();
}

void RenderTask::unbindShader(){
    if(shader_program_)
        shader_program_->unbindProgram();
}

void RenderTask::bindTexture(){
    if(shader_program_ && render_params_){
        // // TODO
        // auto const & texture_info = shader_program_->getTextureInfo();
        // const std::map<TextureType, std::string> & tex_map = render_params_->getTextureMap();
        // TexturePool & texture_pool = TexturePool::getInstance();
        // for(auto const & [var_name, info]: texture_info){
        //     if(tex_map.find(info.type_) != tex_map.end()){
        //         auto tex = texture_pool.getTextureModule(tex_map.at(info.type_));  // TODO
        //         if(tex)
        //             shader_program_->setUniformTexture(var_name, tex);
        //     }
        // }
    }

}

void RenderTask::unbindTexture(){
    if(shader_program_ && render_params_){
        // auto const & texture_info = shader_program_->getTextureInfo();
        //     const std::map<TextureType, std::string> & tex_map = render_params_->getTextureMap();
        //     TexturePool & texture_pool = TexturePool::getInstance();
        //     for(auto const & [var_name, info]: texture_info){
        //         if(tex_map.find(info.type_) != tex_map.end()){
        //             auto tex = texture_pool.getTextureModule(tex_map.at(info.type_));  // TODO
        //             if(tex)
        //                 tex->unbindTexture();
        //         }
        //     }
    }
}

void RenderTask::updateParams(){
    if(shader_program_){
        // auto const & uniform_info = shader_program_->getUniformInfo();
        // // float
        // auto & float_map = render_params_->getFloatMap();
        // for(auto const& iter :float_map){
        //     shader_program_->setUniform1f(iter.first, iter.second);
        // }
        // // vec3
        // auto & vec3_map = render_params_->getVec3Map();
        // for(auto const& iter :vec3_map){
        //     shader_program_->setUniformVec3(iter.first, iter.second);
        // }
        // // mat4
        // auto & mat4_map = render_params_->getMat4Map();
        // for(auto const& iter : mat4_map){
        //     shader_program_->setUniformMat4f(iter.first, iter.second);
        // }
    }
}

void RenderTask::updateAttribute(){
    // if(!shader_program_){
    //     return;
    // }
    // for(const auto & data_entry : data_){
    //     switch (data_entry->getDataLayOut())
    //     {
    //     case VERTEX_POSITION:{
    //         data_entry->setUpLayout(shader_program_->getPosLocation());
    //         break;
    //     }
    //     case VERTEX_NORMAL:{
    //         data_entry->setUpLayout(shader_program_->getNormLocation());
    //         break;
    //     }
    //     case VERTEX_TANGENT:{
    //         data_entry->setUpLayout(shader_program_->getTangentLocation());
    //         break;
    //     }
    //     case VERTEX_BITANGENT:{
    //         data_entry->setUpLayout(shader_program_->getBitangentLocation());
    //         break;
    //     }
    //     case TEXTURE_COORDINATE:{
    //         data_entry->setUpLayout(shader_program_->getUVLocation());
    //         break;
    //     }
    //     default:
    //         break;
    //     }
    // }
}

void RenderTask::applyStatus(){
    if(status_)
        status_->saveAndApply();
}

void RenderTask::resetStatus(){
    if(status_)
        status_->resetStatus();
}

void RenderTask::bindFBO(){
    if(fbo_)
        fbo_->bindFBO();
}

void RenderTask::unbindFBO(){
    if(fbo_)
        fbo_->unbindFBO();
}

void RenderTask::bindDataModule() {
    // for(auto data_mod: data_){
    //     if(data_mod->getBufferType() == "ARRAY_BUFFER"){  // TODO
    //         data_mod->bindDataBuffer();
    //         data_mod->enableVAA();
    //     }
    //     else if(data_mod->getBufferType() == "ELEMENT_ARRAY_BUFFER"){
    //         data_mod->bindDataBuffer();
    //     }
    // }
}

void RenderTask::unbindDataModule() {
    // for(auto data_mod: data_){
    //     if(data_mod->getBufferType() == "ARRAY_BUFFER"){
    //         data_mod->unbindDataBuffer();
    //         data_mod->disableVAA();
    //     }
    //     else if(data_mod->getBufferType() == "ELEMENT_ARRAY_BUFFER"){
    //         data_mod->unbindDataBuffer();
    //     }
    // }
}





}

