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
    // program 
    std::shared_ptr<ShaderModule> program =  ShaderModule::getInstancePtr();
    // vert 
    std::shared_ptr<ShaderSrc> vert_shader = ShaderSrc::getInstancePtr(AE_VERTEX_SHADER);
    vert_shader->setUpShaderSource(shader_info.vert.c_str(), shader_info.vert.length());
    program->attachShaderSrc(vert_shader);
    // frag
    std::shared_ptr<ShaderSrc> frag_shader = ShaderSrc::getInstancePtr(AE_FRAGMENT_SHADER);
    frag_shader->setUpShaderSource(shader_info.frag.c_str(), shader_info.frag.length());
    program->attachShaderSrc(frag_shader);
    // geom
    if(!shader_info.geom.empty()){
        std::shared_ptr<ShaderSrc> geom_shader = ShaderSrc::getInstancePtr(AE_GEOMETRY_SHADER);
        geom_shader->setUpShaderSource(shader_info.frag.c_str(), shader_info.frag.length());
        program->attachShaderSrc(geom_shader);
    }
    // precompliered reference
    for(auto & source: pool.precompliered_sources_){
        program->attachShaderSrc(source);
    }
    
    program->setUpProgram(shader_info.name);
    pool.shader_pool_[shader_info.name] = program;
    return pool.shader_pool_.at(shader_info.name);
}

void ShaderPool::loadShaderSource(const std::string & shader_src, const AE_SHADER_TYPE & type){
    ShaderPool & pool = ShaderPool::getInstance();
    std::shared_ptr<ShaderSrc> source = ShaderSrc::getInstancePtr(type);
    source->setUpShaderSource(shader_src.c_str(), shader_src.length());
    pool.precompliered_sources_.emplace_back(source);
}

std::shared_ptr<ShaderModule> ShaderPool::getShaderModule(const std::string & name) {
    ShaderPool & pool = ShaderPool::getInstance();
    if(pool.shader_pool_.find(name) != pool.shader_pool_.end())
        return pool.shader_pool_.at(name);
    return nullptr;
}

}
