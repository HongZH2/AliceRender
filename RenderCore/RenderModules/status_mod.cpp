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


StatusContainer::StatusContainer(){

}

StatusContainer::StatusContainer(const int32_t & setting){
    status_setting_ = setting;
}

StatusContainer::~StatusContainer(){

}


void StatusContainer::applyStatus(const int32_t & status_setting){
    if(status_setting == none_setting){
        return;
    }
    // TODO
    if(status_setting & reflesh_color){
        status_ops_->clearColorBuffer();
    }
    if(status_setting & reflesh_depth){
        status_ops_->clearDepthBuffer();
    }
    if(status_setting & reflesh_stencil){
        status_ops_->clearStencilBuffer();
    }
    status_ops_->setDepthTest(status_setting & depth_tesh);
    status_ops_->setFaceCull(status_setting & cull_face);
}

void StatusContainer::setBufferColor(const GVec4 & color){
    color_ = color;
    status_ops_->setBufferColor(color_);
}

void StatusContainer::setViewPort(const GVec4i & rect){
    view_ = rect;
    status_ops_->viewport(view_);
}

void StatusContainer::setLineWidth(const float &width){
    line_width_ = width;
    status_ops_->setLineWidth(width);
}

StatusSaver::StatusSaver(){
    // status
    int32_t depth_test = status_ops_->checkDepthTest() << 6;
    int32_t cull_face = status_ops_->checkFaceCull() << 7;
    prev_setting_ = depth_test | cull_face;

    // color and viewport
    prev_view_ = status_ops_->checkViewport();
    prev_color_ = color_;
}

StatusSaver::StatusSaver(const int32_t & setting):
StatusContainer(setting){
     // status
    int32_t depth_test = status_ops_->checkDepthTest() << 6;
    int32_t cull_face = status_ops_->checkFaceCull() << 7;
    prev_setting_ = depth_test | cull_face;
    status_setting_ = setting;
    // color and viewport
    prev_view_ = status_ops_->checkViewport();
    prev_color_ = color_;
}

StatusSaver::~StatusSaver(){
}

void StatusSaver::saveAndApply(int32_t setting){
    status_setting_ = setting;
    saveAndApply();
}

void StatusSaver::saveAndApply(){
    // operations 
    if(status_setting_ & set_colorbuffer)
        status_ops_->setBufferColor(color_);
    if(status_setting_ & set_viewport)
        status_ops_->viewport(view_);
    if(status_setting_ & set_line_width)
        status_ops_->setLineWidth(line_width_);
    applyStatus(status_setting_);
}

void StatusSaver::resetStatus(){
    if(status_setting_ & set_colorbuffer)
        status_ops_->setBufferColor(prev_color_);
    // if(status_setting_ & set_viewport)
    //     status_ops_->viewport(view_); // no need to set back viewport
    applyStatus(prev_setting_); 
}

void StatusSaver::setViewPort(const GVec4i & rect){
    view_ = rect;
    // view_[2] *= FBO_OFFSET;
    // view_[3] *= FBO_OFFSET;
    status_setting_ |= set_viewport;
}

void StatusSaver::setLineWidth(const float &width){
    line_width_ = width;
    status_setting_  |= set_line_width;
}

void StatusSaver::setBufferColor(const GVec4 & color){
    color_ = color;
    status_setting_ |= set_colorbuffer;
}



}
