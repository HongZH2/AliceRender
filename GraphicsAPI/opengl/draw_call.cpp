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
    #ifdef OPENGL_VERSION3
        glDrawArraysInstanced(GL_DEFS[usage_], offset_, num_vertices_, num_instances_);
    #elifdef OPENGL_VERSION2
        glDrawArraysInstancedARB(GL_DEFS[usage_], offset_, num_vertices_, num_instances_);
    #endif // OPENGL_VERSION3
}

void DrawCall::drawElementInstance(){
    #ifdef OPENGL_VERSION3
        glDrawElementsInstanced(GL_DEFS[usage_], num_vertices_, GL_DEFS[data_t_], (void*)(offset_), num_instances_);
    #elifdef OPENGL_VERSION2
        glDrawElementsInstancedARB(GL_DEFS[usage_], num_vertices_, GL_DEFS[data_t_], (void*)(offset_), num_instances_);
    #endif // OPENGL_VERSION3
}

}
