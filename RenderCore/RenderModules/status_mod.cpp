//
// Created by HongZh on 2022/02/25, 11:27:00
//

#include "status_mod.h"
#include "status_call.h"

namespace AliceAPI {



StatusModule::StatusModule(){
    
}

StatusModule::~StatusModule(){

}

std::shared_ptr<StatusModule> StatusModule::getInstancePtr(){
    static std::shared_ptr<StatusModule> instance_ptr = std::make_shared<StatusCall>();
    return instance_ptr;
}


StatusSaver::StatusSaver():status_ops_(StatusModule::getInstancePtr()){

}

StatusSaver::StatusSaver(const StatusTypeFlag & setting):status_ops_(StatusModule::getInstancePtr()){
    cur_.setting_ = setting;
}

StatusSaver::~StatusSaver(){
}

void StatusSaver::saveAndApply(StatusTypeFlag setting){
    cur_.setting_ = setting;
    saveAndApply();
}


void StatusSaver::applyStatus(const StatusTypeFlag & setting){
    // operations 
    if(setting & (StatusTypeFlag)SetBufferColor)
        status_ops_->setBufferColor(cur_.buffer_color_);
    if(setting  & (StatusTypeFlag)SetViewport)
        status_ops_->viewport(cur_.view_);
    if(setting  & (StatusTypeFlag)SetLineWidth)
        status_ops_->setLineWidth(cur_.line_width_);

    if(setting & (StatusTypeFlag)EnableDepthTest){
        status_ops_->enableStatus(AE_DEPTH_TEST, 1);
        status_ops_->setDepthTestFunc(cur_.depth_func_);
    }
    if(setting & (StatusTypeFlag)DisableDepthTest)
        status_ops_->enableStatus(AE_DEPTH_TEST, 0);
    if(setting & (StatusTypeFlag)EnableBlend){
        status_ops_->enableStatus(AE_BLEND, 1);
        status_ops_->setBlendFunc(cur_.src_func_, cur_.dst_func_);
    }
    if(setting & (StatusTypeFlag)DisableBlend)
        status_ops_->enableStatus(AE_BLEND, 0);
    if(setting & (StatusTypeFlag)EnableFaceCull)
        status_ops_->enableStatus(AE_CULL_FACE, 1);
    if(setting & (StatusTypeFlag)DisableFaceCull)
        status_ops_->enableStatus(AE_CULL_FACE, 0);
}

void StatusSaver::saveAndApply(){
    if(!is_initilized_){
        // status
        status_ops_->checkStatus(AE_DEPTH_TEST) ? prev_.setting_ &= (StatusTypeFlag)EnableDepthTest : prev_.setting_ &= (StatusTypeFlag)DisableDepthTest;
        status_ops_->checkStatus(AE_CULL_FACE) ? prev_.setting_ &= (StatusTypeFlag)EnableFaceCull : prev_.setting_ &= (StatusTypeFlag)DisableFaceCull;
        status_ops_->checkStatus(AE_BLEND) ? prev_.setting_ &= (StatusTypeFlag)EnableBlend : prev_.setting_ &= (StatusTypeFlag)DisableBlend;

        // color and viewport
        prev_.view_ = status_ops_->checkViewport();
        is_initilized_ = true;
    }
    applyStatus(cur_.setting_);
}

    

void StatusSaver::resetStatus(){
    if(cur_.setting_ & (StatusTypeFlag)SetBufferColor)
        status_ops_->setBufferColor(prev_.buffer_color_);
    applyStatus(prev_.setting_); 
}

void StatusSaver::setViewPort(const GVec4i & rect){
    cur_.view_ = rect;
    cur_.setting_ |= (StatusTypeFlag)SetViewport;
}

void StatusSaver::setLineWidth(const float &width){
    cur_.line_width_ = width;
    cur_.setting_  |= (StatusTypeFlag)SetLineWidth;
}

void StatusSaver::setBufferColor(const GVec4 & color){
    cur_.buffer_color_ = color;
    cur_.setting_ |= (StatusTypeFlag)SetBufferColor;
}

void StatusSaver::setBlendFunc(const AE_BLEND_FUNC &sfunc, const AE_BLEND_FUNC &dfunc){
    cur_.src_func_ = sfunc;
    cur_.dst_func_ = dfunc;
}

void StatusSaver::setDepthFunc(const AE_DEPTH_TEST_FUNC &dfunc){
    cur_.depth_func_ = dfunc;
}



}
