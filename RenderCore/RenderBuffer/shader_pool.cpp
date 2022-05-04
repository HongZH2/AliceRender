//
// Created by zhanghong50 on 2022/2/1.
//

#include "shader_pool.h"
#include "RenderModules/shader_mod.h"

namespace AliceAPI {


ShaderPool::ShaderPool() {

}

ShaderPool::~ShaderPool() {

}

ShaderPool &ShaderPool::getInstance() {
    static ShaderPool instance;
    return instance;
}

// TODO
void ShaderPool::loadShader(const struct ShaderInfo & shader_info) {
    std::shared_ptr<ShaderModule> program =  ShaderModule::getInstancePtr();
    program->linkVertShader(shader_info.vert.c_str(), shader_info.vert.length());
    program->linkFragShader(shader_info.frag.c_str(), shader_info.frag.length());
    program->setUpProgram(shader_info.name);
    shader_pool_[shader_info.name] = program;
}

std::shared_ptr<ShaderModule> ShaderPool::getShaderModule(const std::string & name) {
    return shader_pool_[name];
}

}
