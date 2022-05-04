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

std::shared_ptr<DrawModule> DrawModule::getInstance(uint32_t n_vertices) {
    std::shared_ptr<DrawModule> instance_ptr = std::make_shared<DrawCall>(n_vertices);
    return instance_ptr;
}


}
