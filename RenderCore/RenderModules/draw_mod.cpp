//
// Created by zhanghong50 on 2022/1/19.
//

#include "draw_mod.h"
#include "draw_call.h"

namespace AliceAPI {


DrawModule::DrawModule() {

}

DrawModule::~DrawModule() {

}

void DrawModule::draw(){
    switch (draw_t_) {
        case AE_DRAW_ARRAY:{
            drawArrays();
            break;
        }
        case AE_DRAW_ELEMENT:{
            drawElement();
            break;
        }
        case AE_DRAW_ARRAY_INSTANCE:{
            drawArraysInstance();
            break;
        }
        case AE_DRAW_ELEMENT_INSTANCE:{
            drawElementInstance();
            break;
        }
    }
}

std::shared_ptr<DrawModule> DrawModule::getInstance(const uint32_t & n_vertices, 
                                                    const AE_DRAWCALL_TYPE & draw_t,
                                                    const AE_DRAWCALL_USEAGE & usage,
                                                    const AE_DATA_TYPE & data_t,
                                                    const uint32_t & n_instances,
                                                    const uint32_t & offset){
    std::shared_ptr<DrawModule> instance_ptr = std::make_shared<DrawCall>();
    instance_ptr->num_vertices_ = n_vertices;
    instance_ptr->draw_t_ = draw_t;
    instance_ptr->usage_ = usage;
    instance_ptr->data_t_ = data_t;
    instance_ptr->offset_ = offset;
    instance_ptr->num_instances_ = n_instances;
    return instance_ptr;
}

void DrawModule::setDrawCallType(const AE_DRAWCALL_TYPE & draw_t){
    draw_t_ = draw_t;
}

void DrawModule::setDrawUsage(const AE_DRAWCALL_USEAGE & usage){
    usage_ = usage;
}

void DrawModule::setNumOfVertices(const uint32_t & n_vertices){
    num_vertices_ = n_vertices;
}

void DrawModule::setNumOfInstances(const uint32_t & n_instances){
    num_instances_ = n_instances;
}

const AE_DRAWCALL_TYPE & DrawModule::getDrawType(){
    return draw_t_;
}

}
