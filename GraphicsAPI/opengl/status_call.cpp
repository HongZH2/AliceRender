//
// Created by HongZh on 2022/02/25, 14:44:59
//

#include "status_call.h"

namespace AliceAPI {


StatusCall::StatusCall(){

}

StatusCall::~StatusCall(){

}


void StatusCall::enableStatus(const AE_STATUS_TYPE &stype, const int32_t &var){
    if(var){
        glEnable(GL_DEFS[stype]);
    }
    else{
        glDisable(GL_DEFS[stype]);
    }
}

int32_t StatusCall::checkStatus(const AE_STATUS_TYPE &stype){
    int32_t var;
    glGetIntegerv(GL_DEFS[stype], &var);
    return var;
}

void StatusCall::setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc){
    glBlendFunc(GL_DEFS[sfunc], GL_DEFS[dfunc]);
}

void StatusCall::setDepthTestFunc(const AE_DEPTH_TEST_FUNC &func){
    glDepthFunc(GL_DEFS[func]);
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

void StatusCall::setLineWidth(const float &width){
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(width);
}



}
