//
// Created by HongZh on 2022/06/25, 23:05:44
//

#ifndef ALICE_ENGINE_SHADER_SRC_H
#define ALICE_ENGINE_SHADER_SRC_H

#include "module_predeclared.h"

namespace AliceAPI{

class ShaderSrc{
public:
    static std::shared_ptr<ShaderSrc> getInstancePtr(const AE_SHADER_TYPE & type);
    virtual ~ShaderSrc();

    virtual void deleteShader() = 0;
    virtual void setUpShaderSource(const char* data, int32_t length) = 0;

    inline uint32_t getShaderID(){return shader_id_;}

protected:
    ShaderSrc();
    AE_SHADER_TYPE type_;
    uint32_t shader_id_;
};

}

#endif //ALICE_ENGINE_SHADER_SRC_H