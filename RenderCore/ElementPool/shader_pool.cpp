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
std::shared_ptr<ShaderModule> ShaderPool::loadShader(const struct ShaderInfo & shader_info) {
    ShaderPool & pool = ShaderPool::getInstance();
    if(pool.shader_pool_.find(shader_info.name) != pool.shader_pool_.end()){
        return pool.shader_pool_.at(shader_info.name);
    }
    std::shared_ptr<ShaderModule> program =  ShaderModule::getInstancePtr();
    program->linkVertShader(shader_info.vert.c_str(), shader_info.vert.length());
    if(!shader_info.geom.empty())  // if there is a geometry shader
        program->linkGeomShader(shader_info.geom.c_str(), shader_info.geom.length());
    program->linkFragShader(shader_info.frag.c_str(), shader_info.frag.length());
    program->setUpProgram(shader_info.name);
    pool.shader_pool_[shader_info.name] = program;
    return pool.shader_pool_.at(shader_info.name);
}

std::shared_ptr<ShaderModule> ShaderPool::getShaderModule(const std::string & name) {
    ShaderPool & pool = ShaderPool::getInstance();
    if(pool.shader_pool_.find(name) != pool.shader_pool_.end())
        return pool.shader_pool_.at(name);
    return nullptr;
}

}
