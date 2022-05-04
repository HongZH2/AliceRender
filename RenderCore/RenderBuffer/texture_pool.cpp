//
// Created by zhanghong50 on 2022/1/26.
//

#include "texture_pool.h"

namespace AliceAPI {


TexturePool::TexturePool(){

}

TexturePool::~TexturePool(){

}

TexturePool & TexturePool::getInstance(){
    static TexturePool instance;
    return instance;
}

std::shared_ptr<TextureModule> TexturePool::getTextureModule(const std::string & name){
    if(texture_.find(name) != texture_.end()){
        return texture_.at(name);
    }
    return nullptr;   // if there is no such texture, return nullptr
}

// load single external texture 
void TexturePool::loadTexture(std::shared_ptr<TextureInfo> & tex_info){
    // check if there is a texture with the same name
    if(texture_.find(tex_info->name_) != texture_.end()){
        deleteTexure(tex_info->name_);
    }

    // create a texture block with one texture module
    std::shared_ptr<TextureBlock> block = TextureBlock::getInstancePtr(tex_info->type_);
    std::shared_ptr<TextureModule> module = std::static_pointer_cast<TextureModule>(tex_info);
    block->addTextureModule(module);
    texture_blocks_.emplace_back(block);
    num_of_blocks_ += 1;

    texture_[tex_info->name_] = module;
    external_tex_[tex_info->name_] = module;
}

void TexturePool::loadInternalTexture(std::shared_ptr<TextureInfo> & tex_info){
    if(texture_.find(tex_info->name_) != texture_.end()){
        deleteTexure(tex_info->name_);
    }

    // create a texture block with one texture module
    std::shared_ptr<TextureBlock> block = TextureBlock::getInstancePtr(tex_info->type_);
    std::shared_ptr<TextureModule> module = std::static_pointer_cast<TextureModule>(tex_info);
    block->addTextureModule(module);
    texture_blocks_.emplace_back(block);
    num_of_blocks_ += 1;

    texture_[tex_info->name_] = module;
    internal_tex_[tex_info->name_] = module;
}

void TexturePool::deleteTexure(const std::string & name){
    if(texture_[name])
        texture_[name]->deleteTexture();
}

const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & TexturePool::getInternalTextures(){
    return internal_tex_;
}

const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & TexturePool::getExternalTextures(){
    return external_tex_;
}

}
