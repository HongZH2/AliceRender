//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_SHADER_MOD_H
#define ALICE_ENGINE_SHADER_MOD_H

#include "texture_mod.h"
#include "module_predeclared.h"

namespace AliceAPI {


struct ShaderInfo{
    std::string vert;
    std::string frag;
    std::string geom;
    std::string name;
};

struct AttachedTexInfo{
    uint32_t loc_;
    uint32_t unit_id_;
    TextureType type_;
};

struct VariableInfo{
    uint32_t loc_;
    uint32_t type_; // FLOAT, VEC3, MAT4 ... 
};


class ShaderModule {
public:
    static std::shared_ptr<ShaderModule> getInstancePtr();
    virtual ~ShaderModule();

    const std::unordered_map<std::string, AttachedTexInfo> & getTextureInfo();
    const std::unordered_map<std::string, VariableInfo> & getUniformInfo();
    const std::unordered_map<std::string, VariableInfo> & getAttribInfo();
    
    virtual void bindProgram() = 0;
    virtual void unbindProgram() = 0;
    virtual void linkVertShader(const char *data, uint32_t length) = 0;
    virtual void linkFragShader(const char *data, uint32_t length) = 0;
    virtual void setUpProgram(const std::string & name) = 0;

    virtual uint32_t getAttribLocation(const std::string & key) = 0;
    virtual uint32_t getUniformLocation(const std::string & key) = 0;
    virtual uint32_t getPosLocation() = 0;
    virtual uint32_t getUVLocation() = 0;
    virtual uint32_t getNormLocation() = 0;
    virtual uint32_t getTangentLocation() = 0;
    virtual uint32_t getBitangentLocation() = 0;

    virtual void setUniform1f(const std::string & key, const float & val) = 0;
    virtual void setUniform1i(const std::string & key, const int32_t & val) = 0;
    virtual void setUniformVec3(const std::string & key, const GVec3 & vec ) = 0;
    virtual void setUniformMat4f(const std::string & key, const GMat4 & mat4_val) = 0;

    virtual void setUniformTexture(const std::string & key, std::shared_ptr<TextureModule> tex) = 0;
    
protected:    
    std::string name_;
    std::unordered_map<std::string, AttachedTexInfo> tex_info_;
    std::unordered_map<std::string, VariableInfo> uniform_info_;
    std::unordered_map<std::string, VariableInfo> attrib_info_;

    ShaderModule();
};

}


#endif //ALICE_ENGINE_SHADER_MOD_H
