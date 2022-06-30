//
// Created by zhanghong50 on 2022/1/26.
//

#ifndef ALICE_ENGINE_SHADER_PROGRAM_H
#define ALICE_ENGINE_SHADER_PROGRAM_H

#include "shader.h"
#include "texture_2d.h"
#include "texture_cube.h"
#include "RenderModules/shader_mod.h"

namespace AliceAPI {


class ShaderProgram: public ShaderModule{
public:
    ShaderProgram();
    ~ShaderProgram();

    // set shader source
    void attachShaderSrc(std::shared_ptr<ShaderSrc> source) override;
    void setUpProgram(const std::string & name) override;    // set up the shader program

    // program
    void bindProgram() override;
    void unbindProgram() override;
    void createProgram();
    void attachSources();
    void linkProgram();
    void getProgramStatus();
    void parseUniforms();
    void parseAttribs();
    void parseUniformBlocks();
    void detachSources();
    void deleteProgram();


    // get uniform location
    // TODO
    int32_t getAttribLocation(const std::string & key) override;
    int32_t getUniformLocation(const std::string &key) override;
    int32_t getUniformBlockIndex(const std::string & key) override;

    void setUniformBlockBinding(uint32_t & index, uint32_t & binding) override;
    void setAttributeVec3(const std::string & key, const GVec3 & vec) override;
    void setAttributeMat4(const std::string & key, const GMat4 & mat) override;

    void setUniform1fv(const std::string & key, std::vector<float> & vals);
    // void setUniform2f(const std::string & key, float val1, float val2);
    // void setUniform3f(const std::string & key, float val1, float val2, float val3) ;
    // void setUniform4f(const std::string & key, float val1, float val2, float val3, float val4);
    void setUniform1f(const std::string & key, const float & val) override;
    void setUniform1i(const std::string & key, const int32_t & val) override;
    void setUniformVec2(const std::string &key, const GVec2 & vec) override;
    void setUniformVec3(const std::string &key, const GVec3 & vec) override;
    void setUniformMat3f(const std::string &key, const GMat3 & mat3_val) override;
    void setUniformMat4f(const std::string &key, const GMat4 & mat4_val) override;
    // TODO: num_tex
    void setUniformTexture(const std::string & key, std::shared_ptr<TextureModule> tex) override;

protected:
    void saveTextureInfo(const std::string & key);
};

}


#endif //ALICE_ENGINE_SHADER_PROGRAM_H
