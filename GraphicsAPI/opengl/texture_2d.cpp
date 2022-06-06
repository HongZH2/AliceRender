//
// Created by zhanghong50 on 2022/1/13.
//

#include "texture_2d.h"

namespace AliceAPI { 


Texture2D::Texture2D(){

}
Texture2D::~Texture2D() {

}

void Texture2D::setUpTexture(std::shared_ptr<TextureModule> tex_mod){
    glBindTexture(GL_DEFS[tex_mod->usage_], tex_mod->tex_id_);
    glTexImage2D(GL_DEFS[tex_mod->usage_], 0, GL_DEFS[tex_mod->interal_type_], tex_mod->width_, tex_mod->height_, 0, GL_DEFS[tex_mod->interal_type_], GL_DEFS[tex_mod->data_t_], tex_mod->buffer_);
    setTextureParams(tex_mod);
    setTextureFilter(tex_mod);
    glBindTexture(GL_DEFS[tex_mod->usage_], 0);
}


void Texture2D:: createTextures(uint32_t * & tex_ids, const uint32_t & num_tex){
    if(!tex_ids){
        tex_ids = (uint32_t*)malloc(num_tex * sizeof(uint32_t));
        glGenTextures(num_tex, tex_ids);
    }
}

void Texture2D::bindTexture(std::shared_ptr<TextureModule> tex_mod) {
    glBindTexture(GL_DEFS[tex_mod->usage_], tex_mod->tex_id_);
}

void Texture2D::unbindTexture(std::shared_ptr<TextureModule> tex_mod) {
    glBindTexture(GL_DEFS[tex_mod->usage_], 0);
}

void Texture2D::setTextureParams(std::shared_ptr<TextureModule> tex_mod) {
    glGenerateMipmap(GL_DEFS[tex_mod->usage_]);
    glTexParameteri(GL_DEFS[tex_mod->usage_], GL_TEXTURE_WRAP_S, GL_DEFS[tex_mod->param_]);
    glTexParameteri(GL_DEFS[tex_mod->usage_], GL_TEXTURE_WRAP_T, GL_DEFS[tex_mod->param_]);
}

void Texture2D::setTextureFilter(std::shared_ptr<TextureModule> tex_mod) {
    glTexParameteri(GL_DEFS[tex_mod->usage_], GL_TEXTURE_MIN_FILTER, GL_DEFS[tex_mod->filter_]);
    glTexParameteri(GL_DEFS[tex_mod->usage_], GL_TEXTURE_MAG_FILTER, GL_DEFS[tex_mod->filter_]);
}

// TODO: 
void Texture2D::deleteTexture(uint32_t * tex_ids, const uint32_t & num_tex) {
    if(tex_ids){
        glDeleteTextures(num_tex, tex_ids);
    }
}


}

