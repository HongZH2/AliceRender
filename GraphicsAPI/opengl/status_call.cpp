//
// Created by HongZh on 2022/02/25, 14:44:59
//

#include "status_call.h"

namespace AliceAPI {


StatusCall::StatusCall(){

}

StatusCall::~StatusCall(){

}

void StatusCall::setFaceCull(const int32_t & var){
    if(var){
        glEnable(GL_CULL_FACE);
    }
    else{
        glDisable(GL_CULL_FACE);
    }
}
int32_t StatusCall::checkFaceCull(){
    int32_t var;
    glGetIntegerv(GL_CULL_FACE, &var);
    return var;
}

void StatusCall::setDepthTest(const int32_t & var){
    if(var){
        glEnable(GL_DEPTH_TEST); 
        glDepthFunc(GL_LESS); 
    }
    else{
        glDisable(GL_DEPTH_TEST);
    }
}
int32_t StatusCall::checkDepthTest(){
    int32_t var;
    glGetIntegerv(GL_DEPTH_TEST, &var);
    return var;
}

void StatusCall::clearColorBuffer(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void StatusCall::clearDepthBuffer(){
    glClear(GL_DEPTH_BUFFER_BIT);
}

void StatusCall::clearStencilBuffer(){
    glClear(GL_STENCIL_BUFFER_BIT);
}
void StatusCall::clearAllBuffer(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void StatusCall::viewport(const GVec4i & rect){
    glViewport(rect[0], rect[1], rect[2], rect[3]);
}

GVec4i StatusCall::checkViewport(){
    GVec4i viewport;
    glGetIntegerv(GL_VIEWPORT, &viewport[0]);
    return viewport;
}

void StatusCall::setBufferColor(const GVec4 & color){
    glClearColor(color[0], color[1], color[2], color[3]);
}



}
