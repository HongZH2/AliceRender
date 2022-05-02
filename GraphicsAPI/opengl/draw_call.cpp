//
// Created by zhanghong50 on 2022/1/26.
//

#include "draw_call.h"


namespace AliceAPI {


DrawCall::DrawCall() {

}
DrawCall::DrawCall(uint32_t n_vertices) {
    num_vertices_ = n_vertices;
}

DrawCall::~DrawCall() {

}

void DrawCall::drawElement() {
    glDrawElements(GL_DEFS[usage_], num_vertices_, GL_UNSIGNED_INT, (void*)(offset_ * sizeof(uint32_t)));
}


void DrawCall::drawArrays() {
    glDrawArrays(GL_DEFS[usage_], 0, num_vertices_);  // to do offset
}

void DrawCall::drawArraysInstance(){
    glDrawArraysInstancedARB(GL_DEFS[usage_], 0, num_vertices_, num_instances_);
}

void DrawCall::drawElementInstance(){
    glDrawElementsInstancedARB(GL_DEFS[usage_], num_vertices_, GL_UNSIGNED_INT, (void*)(offset_ * sizeof(uint32_t)), num_instances_);
}

}
