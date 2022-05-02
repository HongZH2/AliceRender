//
// Created by zhanghong50 on 2022/1/13.
//

#include "texture_2d.h"

namespace AliceAPI {


Texture2D::Texture2D(){

}
Texture2D::~Texture2D() {
    glDeleteTextures(num_tex_,tex_ids_);
    free(tex_ids_);
}

void Texture2D::setUpTexture(){
    createTexture();
    for(uint32_t i = 0; i < num_tex_; i++){
        bindTexture(i);
        glTexImage2D(GL_DEFS[textures_[i]->usage_], 0, GL_DEFS[textures_[i]->interal_type_], textures_[i]->width_, textures_[i]->height_, 0, GL_DEFS[textures_[i]->interal_type_], GL_DEFS[textures_[i]->data_t_], textures_[i]->buffer_);
        setTextureParams(i);
        setTextureFilter(i);
        unbindTexture(i);
    }
}

void Texture2D::createTexture() {
    if(!tex_ids_){
        tex_ids_ = (uint32_t*)malloc(num_tex_ * sizeof(uint32_t));
        glGenTextures(num_tex_, tex_ids_);
    }
}

void Texture2D::bindTexture(const uint32_t & mod_id) {
    glBindTexture(GL_DEFS[textures_[mod_id]->usage_], tex_ids_[mod_id]);
}

void Texture2D::unbindTexture(const uint32_t & mod_id) {
    glBindTexture(GL_DEFS[textures_[mod_id]->usage_], 0);
}

void Texture2D::setTextureParams(const uint32_t & mod_id) {
    glGenerateMipmap(GL_DEFS[textures_[mod_id]->usage_]);
    glTexParameteri(GL_DEFS[textures_[mod_id]->usage_], GL_TEXTURE_WRAP_S, GL_DEFS[textures_[mod_id]->param_]);
    glTexParameteri(GL_DEFS[textures_[mod_id]->usage_], GL_TEXTURE_WRAP_T, GL_DEFS[textures_[mod_id]->param_]);
}

void Texture2D::setTextureFilter(const uint32_t & mod_id) {
    glTexParameteri(GL_DEFS[textures_[mod_id]->usage_], GL_TEXTURE_MIN_FILTER, GL_DEFS[textures_[mod_id]->filter_]);
    glTexParameteri(GL_DEFS[textures_[mod_id]->usage_], GL_TEXTURE_MAG_FILTER, GL_DEFS[textures_[mod_id]->filter_]);
}

// TODO: 
void Texture2D::deleteTexture(const uint32_t & mod_id) {
    if(!tex_ids_){
        glDeleteTextures(num_tex_,tex_ids_);
    }
}


}

