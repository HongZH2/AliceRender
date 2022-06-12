//
// Created by zhanghong50 on 2022/1/26.
//

#ifndef ALICE_ENGINE_SHADER_PROGRAM_H
#define ALICE_ENGINE_SHADER_PROGRAM_H

#include "shader.h"
#include "texture_2d.h"
#include "texture_cube.h"

namespace AliceAPI {


class ShaderProgram: public ShaderModule{
public:
    ShaderProgram();
    ~ShaderProgram();

    // set vertex shader and fragment Shader
    virtual void linkVertShader(const char *data, uint32_t length) override;
    virtual void linkFragShader(const char *data, uint32_t length) override;

    // set up the shader program
    virtual void setUpProgram(const std::string & name) override;

    // program
    virtual void createProgram();
    virtual void attachProgram();
    virtual void linkProgram();
    virtual void getProgramStatus();
    virtual void parseUniforms();
    virtual void parseAttribs();
    virtual void bindProgram() override;
    virtual void unbindProgram() override;
    virtual void deleteProgram();


    // get uniform location
    // TODO
    virtual uint32_t getAttribLocation(const std::string & key) override;
    virtual uint32_t getUniformLocation(const std::string &key) override;
    virtual uint32_t getPosLocation() override;
    virtual uint32_t getUVLocation() override;
    virtual uint32_t getNormLocation() override;
    virtual uint32_t getTangentLocation() override;
    virtual uint32_t getBitangentLocation() override;

    virtual void setAttributeVec3(const std::string & key, const GVec3 & vec) override;
    virtual void setAttributeMat4(const std::string & key, const GMat4 & mat) override;

    virtual void setUniform1fv(const std::string & key, std::vector<float> & vals);
    // virtual void setUniform2f(const std::string & key, float val1, float val2);
    // virtual void setUniform3f(const std::string & key, float val1, float val2, float val3) ;
    // virtual void setUniform4f(const std::string & key, float val1, float val2, float val3, float val4);
    virtual void setUniform1f(const std::string & key, const float & val) override;
    virtual void setUniform1i(const std::string & key, const int32_t & val) override;
    virtual void setUniformVec2(const std::string &key, const GVec2 & vec) override;
    virtual void setUniformVec3(const std::string &key, const GVec3 & vec) override;
    virtual void setUniformMat3f(const std::string &key, const GMat3 & mat3_val) override;
    virtual void setUniformMat4f(const std::string &key, const GMat4 & mat4_val) override;
    // TODO: num_tex
    virtual void setUniformTexture(const std::string & key, std::shared_ptr<TextureModule> tex) override;
protected:
    GLuint unit_c_;
    GLuint program_id_;
    Shader * vert_shader_;
    Shader * frag_shader_;
    Shader * geom_shader_;
    void saveTextureInfo(const std::string & key);
};

}


#endif //ALICE_ENGINE_SHADER_PROGRAM_H
