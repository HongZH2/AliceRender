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


void StatusContainer::applyStatus(){
    if(status_setting_ == none_setting){
        return;
    }
    // TODO
    if(status_setting_ & reflesh_color){
        status_ops_->clearColorBuffer();
    }
    if(status_setting_ & reflesh_depth){
        status_ops_->clearDepthBuffer();
    }
    if(status_setting_ & reflesh_stencil){
        status_ops_->clearStencilBuffer();
    }
    status_ops_->setDepthTest(status_setting_ & depth_tesh);
    status_ops_->setFaceCull(status_setting_ & cull_face);
}

void StatusContainer::setBufferColor(const GVec4 & color){
    color_ = color;
    status_ops_->setBufferColor(color_);
}

void StatusContainer::setViewPort(const GVec4i & rect){
    view_ = rect;
    status_ops_->viewport(view_);
}

StatusSaver::StatusSaver(){

}

StatusSaver::StatusSaver(const int32_t & setting):
StatusContainer(setting){
    
}

StatusSaver::~StatusSaver(){
}

void StatusSaver::saveAndApply(int32_t setting){
    // status
    int32_t depth_test = status_ops_->checkDepthTest() << 6;
    int32_t cull_face = status_ops_->checkFaceCull() << 7;
    prev_setting_ = depth_test | cull_face;
    status_setting_ = setting;

    // operations
    if(status_setting_ & set_colorbuffer)
        status_ops_->setBufferColor(color_);
    if(status_setting_ & set_viewport)
        status_ops_->viewport(view_);
    applyStatus();
}

void StatusSaver::saveAndApply(){
    // status
    int32_t depth_test = status_ops_->checkDepthTest() << 6;
    int32_t cull_face = status_ops_->checkFaceCull() << 7;
    prev_setting_ = depth_test | cull_face;

    // operations // TODO
    if(status_setting_ & set_colorbuffer)
        status_ops_->setBufferColor(color_);
    if(status_setting_ & set_viewport)
        status_ops_->viewport(view_);
    applyStatus();
}

void StatusSaver::resetStatus(){
    status_setting_ = prev_setting_;
    applyStatus();     
}

void StatusSaver::setViewPort(const GVec4i & rect){
    prev_view_ = status_ops_->checkViewport();
    view_ = rect;
    view_[2] *= FBO_OFFSET;
    view_[3] *= FBO_OFFSET;
    status_setting_ |= set_viewport;
}

void StatusSaver::setBufferColor(const GVec4 & color){
    prec_color_ = color_;
    color_ = color;
    status_setting_ |= set_colorbuffer;
}



}
