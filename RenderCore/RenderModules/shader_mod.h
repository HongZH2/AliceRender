//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_SHADER_MOD_H
#define ALICE_ENGINE_SHADER_MOD_H

#include "texture_mod.h"
#include "module_predeclared.h"
#include "RenderModules/shader_src.h"

namespace AliceAPI {


struct ShaderInfo{    
    std::string name;
    std::string vert;
    std::string frag;
    std::string geom;
    uint32_t id;
};

struct AttachedTexInfo{
    uint32_t loc_;
    uint32_t unit_id_;
    TextureType type_;
};


// for default uniform block, it represents location.
// check https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_uniform_buffer_object.txt for more details
struct VariableInfo{  // attribute and uniform in the default uniform block
    int32_t loc_;   
    uint32_t index_;
    // int32_t offset_ = -1;
    // int32_t stride_ = -1;
    AE_DATA_TYPE type_; // FLOAT, VEC3, MAT4 ... 
};

struct UniformBlockInfo{
    uint32_t index_;
    uint32_t binding_ = -1;
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
    // virtual void linkVertShader(const char *data, uint32_t length) = 0;
    // virtual void linkFragShader(const char *data, uint32_t length) = 0;
    // virtual void linkGeomShader(const char *data, uint32_t length) = 0;
    virtual void attachShaderSrc(std::shared_ptr<ShaderSrc>) = 0;
    virtual void setUpProgram(const std::string & name) = 0;

    virtual int32_t getAttribLocation(const std::string & key) = 0;
    virtual int32_t getUniformLocation(const std::string & key) = 0;
    virtual int32_t getUniformBlockIndex(const std::string & key) = 0;

    virtual void setUniformBlockBinding(uint32_t & index, uint32_t & binding) = 0;
    virtual void setAttributeMat4(const std::string & key, const GMat4 & vec) = 0;
    virtual void setAttributeVec3(const std::string & key, const GVec3 & vec) = 0;
    virtual void setUniform1f(const std::string & key, const float & val) = 0;
    virtual void setUniform1i(const std::string & key, const int32_t & val) = 0;
    virtual void setUniformVec2(const std::string &key, const GVec2 & vec) = 0;
    virtual void setUniformVec3(const std::string & key, const GVec3 & vec ) = 0;
    virtual void setUniformMat3f(const std::string &key, const GMat3 & mat3_val) = 0;
    virtual void setUniformMat4f(const std::string & key, const GMat4 & mat4_val) = 0;
    virtual void setUniformTexture(const std::string & key, std::shared_ptr<TextureModule> tex) = 0;
    
protected:    
    std::string name_;
    uint32_t unit_c_;
    uint32_t program_id_;
    // std::shared_ptr<ShaderSrc> vert_shader_ = nullptr;
    // std::shared_ptr<ShaderSrc> frag_shader_ = nullptr;
    // std::shared_ptr<ShaderSrc> geom_shader_ = nullptr;
    // std::shared_ptr<ShaderSrc> func_shader_ = nullptr;
    std::vector<std::shared_ptr<ShaderSrc>> attached_shaders_;
    std::unordered_map<std::string, AttachedTexInfo> tex_info_;
    std::unordered_map<std::string, UniformBlockInfo> uniform_block_info_;   // uniform index
    std::unordered_map<std::string, VariableInfo> uniform_info_;
    std::unordered_map<std::string, VariableInfo> attrib_info_;

    ShaderModule();
};

}


#endif //ALICE_ENGINE_SHADER_MOD_H
