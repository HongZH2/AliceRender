//
// Created by zhanghong50 on 2022/1/13.
//

#include "shader.h"
#include "RenderLog/render_log.h"
#include "graphic_predeclared.h"
#include <cstring>

namespace AliceAPI {


Shader::Shader(AE_SHADER_TYPE type) {
    shader_id_ = -1;
    type_ = type;
}

Shader::~Shader() {

}

void Shader::createShader() {
    shader_id_ = glCreateShader(type_);
}

void Shader::linkShaderSource(const char *data, int32_t length) {
    const GLchar* shader_data[1] = { data };
    GLint lengths[1] = { (length<0) ? (int32_t)(strlen(data)) : length };
    glShaderSource(shader_id_, 1, shader_data, lengths);
}

void Shader::compileShader() {
    glCompileShader(shader_id_);
}

void Shader::getShaderStatus() {
    GLint len_log, slen;
    glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &len_log);
    if(len_log > 1){
        auto compiler_log = (GLcharARB*)malloc(len_log);
        glGetShaderInfoLog(shader_id_, len_log, &slen, compiler_log);
        RenderLog & render_log = RenderLog::getInstance();
        std::string s_type;
        type_ == AE_VERTEX_SHADER ? s_type = "Vertex": s_type = "Fragment"; 
        render_log.submitLog("-- %s Shader Error : \n%s\n", s_type.c_str(), compiler_log);
        free(compiler_log);
    }
}

void Shader::deleteShader() {
    glDeleteShader(shader_id_);
}

}

