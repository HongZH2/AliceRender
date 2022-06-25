//
// Created by HongZh on 2022/06/25, 23:17:33
//

#include "shader_src.h"
#include "shader.h"

namespace AliceAPI {

ShaderSrc::ShaderSrc(){

}

ShaderSrc::~ShaderSrc(){

}

std::shared_ptr<ShaderSrc> ShaderSrc::getInstancePtr(const AE_SHADER_TYPE &type){
    std::shared_ptr<Shader> instance_ptr = std::make_shared<Shader>(type);
    return instance_ptr;
}

}