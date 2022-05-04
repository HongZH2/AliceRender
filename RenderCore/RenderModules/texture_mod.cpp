//
// Created by zhanghong50 on 2022/1/19.
//

#include "texture_mod.h"
#include "texture_2d.h"
#include "texture_cube.h"

namespace AliceAPI {

TextureInfo::TextureInfo(){

}

TextureInfo::~TextureInfo(){
    releaseBuffer();
}


TextureInfo::TextureInfo(int32_t w, int32_t h, int32_t c, TextureType t):
width_(w),
height_(h),
channel_(c),
type_(t){

}

void TextureInfo::releaseBuffer(){
    if(buffer_){
        delete buffer_;
    }
    buffer_ = nullptr;
    
    // delete all the rests of textures
   if(next_ != nullptr){
       next_->releaseBuffer();
   }
}


TextureBlock::TextureBlock() {

}

TextureBlock::~TextureBlock() {

}

std::shared_ptr<TextureBlock> TextureBlock::getInstancePtr(const TextureType & type){
    std::shared_ptr<TextureBlock> tex_mod; 
    switch (type) {
        case CubeMapTexture:{   
            tex_mod = std::make_shared<TextureCube>();
            break;
        }
        default:{
            tex_mod = std::make_shared<Texture2D>();
            break;
        }
    }
    return tex_mod;
}

void TextureBlock::addTextureModule(const std::shared_ptr<TextureModule> & tex){
    textures_.emplace_back(tex);
    tex->mod_id_ = num_tex_;
    num_tex_ += 1;
}

TextureModule::TextureModule(){

}

TextureModule::~TextureModule(){

}


void TextureModule::bindTexture(){
    block_->bindTexture(mod_id_);
}

void TextureModule::unbindTexture(){
    block_->unbindTexture(mod_id_);
}

void TextureModule::deleteTexture(){
    block_->deleteTexture(mod_id_);
}


}


