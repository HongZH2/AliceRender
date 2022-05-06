//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_SHADER_H
#define ALICE_ENGINE_SHADER_H

#include "graphic_predeclared.h"
#include "RenderModules/shader_mod.h"

namespace AliceAPI {


class Shader {
public:
    Shader(AE_SHADER_TYPE type);
    ~Shader();

    // shader
    virtual void createShader();
    virtual void linkShaderSource(const char* data, int32_t length);
    virtual void compileShader();
    virtual void getShaderStatus();
    virtual void deleteShader();
public:
    GLuint shader_id_;
    AE_SHADER_TYPE type_;

};

}


#endif //ALICE_ENGINE_SHADER_H
