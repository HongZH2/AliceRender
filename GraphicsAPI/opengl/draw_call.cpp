//
// Created by zhanghong50 on 2022/1/26.
//

#include "draw_call.h"


namespace AliceAPI {


DrawCall::DrawCall() {

}

DrawCall::~DrawCall() {

}

void DrawCall::drawElement() {
    glDrawElements(GL_DEFS[usage_], num_vertices_, GL_DEFS[data_t_], (void*)(offset_));
}

void DrawCall::drawArrays() {
   glDrawArrays(GL_DEFS[usage_], offset_, num_vertices_);  // to do offset
}

void DrawCall::drawArraysInstance(){
    glDrawArraysInstancedARB(GL_DEFS[usage_], offset_, num_vertices_, num_instances_);
}

void DrawCall::drawElementInstance(){
    glDrawElementsInstancedARB(GL_DEFS[usage_], num_vertices_, GL_DEFS[data_t_], (void*)(offset_), num_instances_);
}

}
