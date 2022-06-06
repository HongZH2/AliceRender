//
// Created by HongZh on 2022/03/07, 14:55:51
//

#include "texture_cube.h"

namespace AliceAPI {


TextureCube::TextureCube(): Texture2D(){

}

TextureCube::~TextureCube(){

}

void TextureCube::setUpTexture(std::shared_ptr<TextureModule> tex_mod){
    glBindTexture(GL_DEFS[tex_mod->usage_], tex_mod->tex_id_);
    std::shared_ptr<TextureModule> tex_info = tex_mod;
    while(tex_info){
        glTexImage2D(GL_DEFS[tex_info->usage_], 0, GL_DEFS[tex_info->interal_type_], tex_info->width_, tex_info->height_, 0, GL_DEFS[tex_info->interal_type_], GL_DEFS[tex_info->data_t_], tex_info->buffer_);
        tex_info = std::static_pointer_cast<TextureModule>(tex_info->next_);
    }
    setTextureParams(tex_mod);
    setTextureFilter(tex_mod);
    unbindTexture(tex_mod);
}


void TextureCube::setTextureParams(std::shared_ptr<TextureModule> tex_mod) {
    AE_TEXTURE_USEAGE usage = tex_mod->usage_;
    AE_TEXTURE_PARAM param = tex_mod->param_;
    glGenerateMipmap(GL_DEFS[usage]);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glTexParameteri(GL_DEFS[usage], GL_TEXTURE_WRAP_S, GL_DEFS[param]);
    glTexParameteri(GL_DEFS[usage], GL_TEXTURE_WRAP_T, GL_DEFS[param]);
    glTexParameteri(GL_DEFS[usage], GL_TEXTURE_WRAP_R, GL_DEFS[param]);
}




}
