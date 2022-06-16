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
    TexturePool & instance = TexturePool::getInstance();
    if(instance.texture_.find(name) != instance.texture_.end()){
        return instance.texture_.at(name);
    }
    return nullptr;   // if there is no such texture, return nullptr
}

// load single external texture 
std::shared_ptr<TextureModule> TexturePool::loadTexture(std::shared_ptr<TextureModule> & tex_mod){
    TexturePool & instance = TexturePool::getInstance();
    // check if there is a texture with the same name
    if(instance.texture_.find(tex_mod->name_) != instance.texture_.end()){
        deleteTexure(tex_mod->name_);
    }
    // create a texture block with one texture module
    std::shared_ptr<TextureBlock> block = std::make_shared<TextureBlock>(tex_mod->type_);
    block->addTextureModule(tex_mod);
    block->setUpTexture();
    tex_mod->block_ = block;

    instance.texture_blocks_.emplace_back(block);
    instance.num_of_blocks_ += 1;
    instance.texture_[tex_mod->name_] = tex_mod;
    instance.external_tex_[tex_mod->name_] = tex_mod;
    return tex_mod;
}

std::shared_ptr<TextureModule> TexturePool::loadInternalTexture(std::shared_ptr<TextureModule> & tex_mod){
    TexturePool & instance = TexturePool::getInstance();
    if(instance.texture_.find(tex_mod->name_) != instance.texture_.end()){
        deleteTexure(tex_mod->name_);
    }

    // create a texture block with one texture module
    std::shared_ptr<TextureBlock> block = std::make_shared<TextureBlock>(tex_mod->type_);

    block->addTextureModule(tex_mod);
    block->setUpTexture();
    tex_mod->block_ = block;
    
    instance.texture_blocks_.emplace_back(block);
    instance.num_of_blocks_ += 1;
    instance.texture_[tex_mod->name_] = tex_mod;
    instance.internal_tex_[tex_mod->name_] = tex_mod;
    return tex_mod;
}

void TexturePool::loadBatchedTexture(std::vector<std::shared_ptr<TextureModule>> & textures, const TextureType & type){
    TexturePool & instance = TexturePool::getInstance();

    // create a texture block with one texture module
    std::shared_ptr<TextureBlock> block = std::make_shared<TextureBlock>(ColorTexture);
    for(auto & tex: textures){
        if(instance.texture_.find(tex->name_) != instance.texture_.end()){
            deleteTexure(tex->name_);
        }
        block->addTextureModule(tex);   
        tex->block_ = block;
        instance.texture_[tex->name_] = tex;
        instance.internal_tex_[tex->name_] = tex;
    }
    block->setUpTexture();

    instance.texture_blocks_.emplace_back(block);
    instance.num_of_blocks_ += 1;
}

void TexturePool::loadAssetTextures(std::vector<std::shared_ptr<TextureModule>> & textures){
    TexturePool & instance = TexturePool::getInstance();
    // create a texture block with one texture module
    std::shared_ptr<TextureBlock> block = std::make_shared<TextureBlock>(ColorTexture);
    for(auto & tex: textures){
        if(instance.texture_.find(tex->name_) != instance.texture_.end()){
            deleteTexure(tex->name_);
        }
        block->addTextureModule(tex);   
        tex->block_ = block;
        instance.texture_[tex->name_] = tex;
        instance.asset_tex_[tex->name_] = tex;
    }
    block->setUpTexture();

    instance.texture_blocks_.emplace_back(block);
    instance.num_of_blocks_ += 1;
}

void TexturePool::deleteTexure(const std::string & name){
    TexturePool & instance = TexturePool::getInstance();
    if(instance.texture_[name])
        instance.texture_[name]->deleteTexture();
}

const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & TexturePool::getInternalTextures(){
    TexturePool & instance = TexturePool::getInstance();
    return instance.internal_tex_;
}

const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & TexturePool::getExternalTextures(){
    TexturePool & instance = TexturePool::getInstance();
    return instance.external_tex_;
}

const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & TexturePool::getAssetTextures(){
    TexturePool & instance = TexturePool::getInstance();
    return instance.asset_tex_;
}

}
