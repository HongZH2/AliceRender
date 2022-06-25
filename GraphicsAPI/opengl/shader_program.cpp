//
// Created by zhanghong50 on 2022/1/26.
//

#include "shader_program.h"

namespace AliceAPI {


ShaderProgram::ShaderProgram(){
    program_id_ = -1;
    unit_c_ = 0;
    createProgram();
}

ShaderProgram::~ShaderProgram() {

}

// void ShaderProgram::linkVertShader(const char *data, uint32_t length) {
//     // generate Shader
//     vert_shader_->createShader();
//     vert_shader_->linkShaderSource(data, length);
//     vert_shader_->compileShader();
//     vert_shader_->getShaderStatus();
// }

// void ShaderProgram::linkFragShader(const char *data, uint32_t length) {
//     frag_shader_->createShader();
//     frag_shader_->linkShaderSource(data, length);
//     frag_shader_->compileShader();
//     frag_shader_->getShaderStatus();
// }

// void ShaderProgram::linkGeomShader(const char *data, uint32_t length){
//     if(!geom_shader_) 
//         geom_shader_ = new Shader(AE_GEOMETRY_SHADER);
//     geom_shader_->createShader();
//     geom_shader_->linkShaderSource(data, length);
//     geom_shader_->compileShader();
//     geom_shader_->getShaderStatus();
// }

void ShaderProgram::attachShaderSrc(std::shared_ptr<ShaderSrc> source){
    attached_shaders_.emplace_back(source);
}

void ShaderProgram::setUpProgram(const std::string & name) {
    name_ = name;
    attachSources();
    linkProgram();
    getProgramStatus();
    parseUniforms();
    parseAttribs();
    parseUniformBlocks();
    detachSources();
}

void ShaderProgram::createProgram() {
    program_id_ = glCreateProgram();
}

void ShaderProgram::attachSources(){
    for(auto & shader_src: attached_shaders_){
        glAttachShader(program_id_, shader_src->getShaderID());
    }
}

void ShaderProgram::detachSources(){
    attached_shaders_.clear();
}

// deal will all kinds of textures
void ShaderProgram::saveTextureInfo(const std::string & key){
    for(auto const & [type, prefix]: tex_prefix){
        if(key.find(prefix) != std::string::npos){
                struct AttachedTexInfo info;
                info.loc_ = getUniformLocation(key);
                info.unit_id_ = unit_c_;
                info.type_ = type;
                glUniform1i(info.loc_, unit_c_++);  // assign a texture unit 
                tex_info_[key] = std::move(info);
                break;
        }
    }
}

void ShaderProgram::parseUniforms(){
    GLint i, count;
    GLint size;
    GLenum type;
    const GLsizei buf_size = 64;
    GLchar name[buf_size];
    GLsizei length;
    glGetProgramiv(program_id_, GL_ACTIVE_UNIFORMS, &count);

    for(i = 0; i < count; i++){
        glGetActiveUniform(program_id_, (GLuint)i, buf_size, &length, &size, &type, name);
        switch(type){
            case AE_SAMPLER_2D:
            case AE_SAMPLER_CUBE:{
                std::string key(name);
                saveTextureInfo(key);
            }
            default:{ //TODO
                struct VariableInfo info;
                info.loc_ = getUniformLocation(name);
                info.index_ = i;
                info.type_ = (AE_DATA_TYPE) GL_CAST[type];
                uniform_info_[name] = std::move(info);
                break;
            }
        }
    }
}

// parse all the attributes
void ShaderProgram::parseAttribs(){
    GLint i, count;
    GLint size;
    GLenum type;
    const GLsizei buf_size = 64;
    GLchar name[buf_size];
    GLsizei length;
    glGetProgramiv(program_id_, GL_ACTIVE_ATTRIBUTES, &count);
    for(i = 0; i < count; i++){
        glGetActiveAttrib(program_id_, (GLuint)i, buf_size, &length, &size, &type, name);  // store the loc of attributes
        struct VariableInfo info;
        info.loc_ = getAttribLocation(name);
        info.type_ = (AE_DATA_TYPE) GL_CAST[type];
        attrib_info_[name] = std::move(info);
    }
}

// parse Uniform Blocks
void ShaderProgram::parseUniformBlocks(){
    GLint i, count;
    GLuint index;
    glGetProgramiv(program_id_, GL_ACTIVE_UNIFORM_BLOCKS, &count);
    for(i = 0; i < count; i++){
        GLsizei length;
        const GLsizei buf_size = 64;
        GLchar name[buf_size];
        glGetActiveUniformBlockiv(program_id_, (GLuint)i, GL_UNIFORM_BLOCK_NAME_LENGTH, &length);
        glGetActiveUniformBlockName(program_id_, (GLuint)5i, length, NULL, name);
        struct UniformBlockInfo block_info;
        block_info.index_ = getUniformBlockIndex(name);

        // bind the uniform block
        for(auto & [type, binding]: uniform_block_bindings){
            std::string key = remain_key[type];
            if(key.find(std::string(name)) != std::string::npos){
                setUniformBlockBinding(block_info.index_, binding);
                block_info.binding_ = binding;
                break;
            }
        }
        uniform_block_info_[name] = std::move(block_info);
    }
}

void ShaderProgram::linkProgram() {
    #ifdef OPENGL_VERSION2
        glBindAttribLocation(program_id_, 0, remain_key.at(VERTEX_POSITION).c_str());
    #endif // OPENGL_VERSION2
    glLinkProgram(program_id_);
}

void ShaderProgram::deleteProgram() {
    glDeleteProgram(program_id_);
}

void ShaderProgram::bindProgram() {
    glUseProgram(program_id_);
}

void ShaderProgram::unbindProgram() {
    glUseProgram(0);
}

void ShaderProgram::getProgramStatus() {
    GLint len_log, slen;
    glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &len_log);
    if(len_log > 1){
        auto compiler_log = (GLcharARB*)malloc(len_log);
        glGetProgramInfoLog(program_id_, len_log, &slen, compiler_log);
        printf(" -- Shader Program Error : \n%s\n", compiler_log);
        free(compiler_log);
    }
}

int32_t ShaderProgram::getAttribLocation(const std::string &key) {
    if(attrib_info_.find(key) != attrib_info_.end()){
        return attrib_info_.at(key).loc_;
    }
    return glGetAttribLocation(program_id_, key.c_str());
}

int32_t ShaderProgram::getUniformLocation(const std::string &key) {
    if(uniform_info_.find(key) != uniform_info_.end()){
        return uniform_info_.at(key).loc_;
    }
    return glGetUniformLocation(program_id_, key.c_str());
}

int32_t ShaderProgram::getUniformBlockIndex(const std::string & key){
    if(uniform_block_info_.find(key) != uniform_block_info_.end()){
        return uniform_block_info_.at(key).index_;   // index 
    } // TODO
    return glGetUniformBlockIndex(program_id_, key.c_str());
}

void ShaderProgram::setUniformBlockBinding(uint32_t & index, uint32_t & binding){   
    glUniformBlockBinding(program_id_, index , binding);
}


void ShaderProgram::setUniform1f(const std::string &key, const float &val) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glUniform1f(loc, val);
    }
}

void ShaderProgram::setUniform1fv(const std::string &key, std::vector<float> & vals) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glUniform1fv(loc, vals.size(), &vals[0]);
    }
}

void ShaderProgram::setAttributeVec3(const std::string &key, const GVec3 &vec){
    GLint loc = getAttribLocation(key);
    if((int) loc != -1){
        glVertexAttrib3fv(loc, &vec[0]);
    }
}

void ShaderProgram::setAttributeMat4(const std::string &key, const GMat4 &mat){
    GLint loc = getAttribLocation(key);
    if((int) loc != -1){
        glVertexAttrib4fv(loc, &mat[0][0]);
        glVertexAttrib4fv(loc + 1, &mat[1][0]);
        glVertexAttrib4fv(loc + 2, &mat[2][0]);
        glVertexAttrib4fv(loc + 3, &mat[3][0]);
    }
}

// void ShaderProgram::setUniform2f(const std::string &key, float val1, float val2) {
//     GLint loc = getUniformLocation(key);
//     if((int) loc != -1){
//         glUniform2f(loc, val1, val2);
//     }
// }

// void ShaderProgram::setUniform3f(const std::string &key, float val1, float val2, float val3) {
//     GLint loc = getUniformLocation(key);
//     if((int) loc != -1){
//         glUniform3f(loc, val1, val2, val3);
//     }
// }

// void ShaderProgram::setUniform4f(const std::string &key, float val1, float val2, float val3, float val4) {
//     GLint loc = getUniformLocation(key);
//     if((int) loc != -1){
//         glUniform4f(loc, val1, val2, val3, val4);
//     }
// }

void ShaderProgram::setUniformMat3f(const std::string &key, const GMat3 &mat3_val) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glUniformMatrix3fv(loc, 1, GL_FALSE, & mat3_val[0][0]);
    }
}

void ShaderProgram::setUniformMat4f(const std::string &key, const GMat4 &mat4_val) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glUniformMatrix4fv(loc, 1, GL_FALSE, & mat4_val[0][0]);
    }
}

void ShaderProgram::setUniformVec2(const std::string &key, const GVec2 &vec) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glUniform2fv(loc, 1, &vec[0]);
    }
}

void ShaderProgram::setUniformVec3(const std::string &key, const GVec3 &vec) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glUniform3fv(loc, 1, &vec[0]);
    }
}

void ShaderProgram::setUniform1i(const std::string &key, const GLint &val) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glUniform1i(loc, val);
    }
}

// TODO 
void ShaderProgram::setUniformTexture(const std::string &key, std::shared_ptr<TextureModule> tex) {
    GLint loc = getUniformLocation(key);
    if((int) loc != -1){
        glActiveTexture(GL_TEXTURE0 + tex_info_.at(key).unit_id_);
        tex->bindTexture();
        // glUniform1i(loc, tex_m->unit_id_);
        //tex_m->unbindTexture();
    }
}


}
