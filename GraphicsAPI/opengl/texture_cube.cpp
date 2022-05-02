//
// Created by HongZh on 2022/03/07, 14:55:51
//

#include "texture_cube.h"

namespace AliceAPI {


TextureCube::TextureCube(): Texture2D(){

}

TextureCube::~TextureCube(){

}

void TextureCube::setUpTexture(){
    createTexture();
    for(uint32_t id = 0; id < num_tex_; id++){
        bindTexture(id);
        auto tex_info = textures_[id];
        while(tex_info){
            glTexImage2D(GL_DEFS[textures_[id]->usage_], 0, GL_DEFS[textures_[id]->interal_type_], textures_[id]->width_, textures_[id]->height_, 0, GL_DEFS[textures_[id]->interal_type_], GL_DEFS[textures_[id]->data_t_], textures_[id]->buffer_);
            tex_info = std::static_pointer_cast<TextureModule>(tex_info->next_);
        }
        setTextureParams(id);
        setTextureFilter(id);
        unbindTexture(id);
    }
}


void TextureCube::setTextureParams(const uint32_t & mod_id) {
    AE_TEXTURE_USEAGE usage = textures_[mod_id]->usage_;
    AE_TEXTURE_PARAM param = textures_[mod_id]->param_;
    glGenerateMipmap(GL_DEFS[usage]);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glTexParameteri(GL_DEFS[usage], GL_TEXTURE_WRAP_S, GL_DEFS[param]);
    glTexParameteri(GL_DEFS[usage], GL_TEXTURE_WRAP_T, GL_DEFS[param]);
    glTexParameteri(GL_DEFS[usage], GL_TEXTURE_WRAP_R, GL_DEFS[param]);
}




}
