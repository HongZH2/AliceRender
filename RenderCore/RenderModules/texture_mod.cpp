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


TextureInfo::TextureInfo(const int32_t & w, const int32_t & h, const int32_t & c, const TextureType & type, const std::string & name):
width_(w),
height_(h),
channel_(c),
type_(type),
name_(name){

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


std::shared_ptr<TextureAllocator> TextureAllocator::getInstancePtr(const TextureType & type){
    std::shared_ptr<TextureAllocator> tex_mod; 
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

TextureBlock::TextureBlock(const TextureType &type){
    allocator_ = TextureAllocator::getInstancePtr(type);
}

TextureBlock::~TextureBlock() {
    releaseBlock();
}

void TextureBlock::addTextureModule(const std::shared_ptr<TextureModule> & tex){
    textures_.emplace_back(tex);
    tex->mod_id_ = num_tex_;
    num_tex_ += 1;
}

void TextureBlock::setUpTexture(){
    allocator_->createTextures(tex_ids_, num_tex_);
    for(size_t id = 0; id < num_tex_; ++id){
        textures_[id]->tex_id_ = *(tex_ids_ + id);
        allocator_->setUpTexture(textures_[id]);
    }
}

void TextureBlock::releaseBlock(){
    allocator_->deleteTexture(tex_ids_, num_tex_);
    if(tex_ids_){
        free(tex_ids_);
    }
}

void TextureBlock::deleteTexture(uint32_t &mod_id){
    allocator_->deleteTexture(&textures_[mod_id]->tex_id_, 1);
}

void TextureBlock::bind(uint32_t &mod_id){
    allocator_->bindTexture(textures_[mod_id]);
}

void TextureBlock::unbind(uint32_t & mod_id){
    allocator_->unbindTexture(textures_[mod_id]);
}


TextureModule::TextureModule(){

}

TextureModule::~TextureModule(){

}


void TextureModule::bindTexture(){
    if(auto block = block_.lock())
        block->bind(mod_id_);
}

void TextureModule::unbindTexture(){
 if(auto block = block_.lock())
        block->unbind(mod_id_);
}

void TextureModule::deleteTexture(){
    if(auto block = block_.lock())
        block->deleteTexture(mod_id_);
}

TextureAllocator::TextureAllocator(){

}

TextureAllocator::~TextureAllocator(){

}

}


