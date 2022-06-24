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

void StatusCall::setDepthTestFunc(const AE_TEST_FUNC &func){
    glDepthFunc(GL_DEFS[func]);
}

void StatusCall::setStencilTestFunc(const AE_TEST_FUNC &func, const int32_t &ref, const uint32_t &mask){
    glStencilFunc(GL_DEFS[func], ref, mask);
}

void StatusCall::setStencilOps(const AE_TEST_OPS & sfail, const AE_TEST_OPS & dpfail, const AE_TEST_OPS & dppass){
    glStencilOp(GL_DEFS[sfail], GL_DEFS[dpfail], GL_DEFS[dppass]);    
}

void StatusCall::setPolygonMode(const AE_POLYGON_MODE_TYPE & pmode){
    glPolygonMode(GL_FRONT_AND_BACK, GL_DEFS[pmode]);
}

void StatusCall::clearBuffer(const AE_COLOR_BUFFER_MASK & mask){
    glClear(GL_DEFS[mask]);
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

void StatusCall::setStencilMask(const uint8_t &mask){
    glStencilMask(mask);
}

void StatusCall::setLineWidth(const float &width){
    // glEnable(GL_LINE_SMOOTH);
    // glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(width);
}



}
