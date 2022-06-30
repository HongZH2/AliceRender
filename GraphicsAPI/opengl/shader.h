//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_SHADER_H
#define ALICE_ENGINE_SHADER_H

#include "graphic_predeclared.h"
#include "RenderModules/shader_src.h"

namespace AliceAPI {


class Shader : public ShaderSrc{
public:
    explicit Shader(const AE_SHADER_TYPE & type);
    ~Shader();

    // shader
    void createShader();
    void linkShaderSource(const char* data, int32_t length);
    void compileShader();
    void getShaderStatus();
    void setUpShaderSource(const char* data, int32_t length) override;
    void deleteShader() override;
};

}


#endif //ALICE_ENGINE_SHADER_H
