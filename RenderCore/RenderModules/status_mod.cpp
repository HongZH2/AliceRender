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

StatusSaver::~StatusSaver(){
}

void StatusSaver::saveAndApply(){
    // states
    // enable all the states in the enable_list
    for(auto & flag: enable_list_){
        status_ops_->enableStatus(flag, 1);
    }
    // disable all the states in the disable_list
    for(auto & flag: disable_list_){
        status_ops_->enableStatus(flag, 0);
    }

    // operations
    for(auto ops: operations_){
        ops(cur_);
    }
}

void StatusSaver::resetStatus(){
    // enable all the states in the disable_list
    for(auto & flag: disable_list_){
        status_ops_->enableStatus(flag, 1);
    }
    // disable all the states in the enable_list
    for(auto & flag: enable_list_){
        status_ops_->enableStatus(flag, 0);
    }

    // operations
    // for(auto ops: operations_){
    //     ops(prev_);
    // }
}

void StatusSaver::setViewPort(const GVec4i & rect){
    cur_.view_ = rect;
    if(!(cur_.ops_mask_ & Ops_ViewPort)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->viewport(stat.view_);
        });
        cur_.ops_mask_ |= Ops_ViewPort;
    }
}

void StatusSaver::setLineWidth(const float &width){
    cur_.line_width_ = width;
    if(!(cur_.ops_mask_ & Ops_Line_Width)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setLineWidth(stat.line_width_);
        });
        cur_.ops_mask_ |= Ops_Line_Width;
    }
}

void StatusSaver::setBufferColor(const GVec4 & color){
    cur_.buffer_color_ = color;
    if(!(cur_.ops_mask_ & Ops_Buffer_Col)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setBufferColor(stat.buffer_color_);
        });
        cur_.ops_mask_ |= Ops_Buffer_Col;
    }
}

void StatusSaver::clearBufferBit(const AE_COLOR_BUFFER_MASK & mask){
    cur_.buffer_mask_ = mask;
    if(!(cur_.ops_mask_ & Ops_Buffer_Msk)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->clearBuffer(stat.buffer_mask_);
        });
        cur_.ops_mask_ |= Ops_Buffer_Msk;
    }
}

void StatusSaver::setBlendFunc(const AE_BLEND_FUNC &sfunc, const AE_BLEND_FUNC &dfunc){
    cur_.src_func_ = sfunc;
    cur_.dst_func_ = dfunc;
    if(!(cur_.ops_mask_ & Ops_Blend_Func)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setBlendFunc(stat.src_func_, stat.dst_func_);
        });
        cur_.ops_mask_ |= Ops_Blend_Func;
    }
}

void StatusSaver::setDepthFunc(const AE_TEST_FUNC &dfunc){
    cur_.depth_func_ = dfunc;
    if(!(cur_.ops_mask_ & Ops_Depth_Func)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setDepthTestFunc(stat.depth_func_);
        });
        cur_.ops_mask_ |= Ops_Depth_Func;
    }
}

void StatusSaver::setStencilFunc(const AE_TEST_FUNC &func, const int32_t &ref, const uint32_t &mask){
    cur_.stencil_func_ = func;
    cur_.stencil_ref_ = ref;
    cur_.stencil_func_mask_ = mask;
    if(!(cur_.ops_mask_ & Ops_Stencil_Func)) {
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setStencilTestFunc(stat.stencil_func_, stat.stencil_ref_, stat.stencil_func_mask_);
        });
        cur_.ops_mask_ |= Ops_Stencil_Func;
    }
}

void StatusSaver::setStencilOps(const AE_TEST_OPS &sfail, const AE_TEST_OPS &dpfail, const AE_TEST_OPS &dppass){
    // TODO: check status
    cur_.sfail_ = sfail;
    cur_.dpfail_ = dpfail;
    cur_.dppass_ = dppass;
    if(!(cur_.ops_mask_ & Ops_Stencil_Ops)) {
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setStencilOps(stat.sfail_, stat.dpfail_, stat.dppass_);
        });
        cur_.ops_mask_ |= Ops_Stencil_Ops;
    }
}

void StatusSaver::setPolygonMode(const AE_POLYGON_MODE_TYPE &pmode){
    cur_.polygon_mode_ = pmode;
    if(!(cur_.ops_mask_ & Ops_Polygon_model)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setPolygonMode(stat.polygon_mode_);
        });
        cur_.ops_mask_ |= Ops_Polygon_model;
    }
}

void StatusSaver::setStencilMask(const uint8_t &stencil_mask){
    cur_.stencil_mask_ = stencil_mask;
    if(!(cur_.ops_mask_ & Ops_Stencil_Msk)){
        operations_.emplace_back([&](StatusContainer & stat){
            status_ops_->setStencilMask(stat.stencil_mask_);
        });
        cur_.ops_mask_ |= Ops_Stencil_Msk;
    }
}



}
