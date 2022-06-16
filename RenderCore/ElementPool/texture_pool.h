//
// Created by zhanghong50 on 2022/1/26.
//

#ifndef ALICE_ENGINE_TEXTURE_POOL_H
#define ALICE_ENGINE_TEXTURE_POOL_H

#include "RenderModules/texture_mod.h"

namespace AliceAPI {

/* 
* class for Texture Pool to manager texture 
*/

class TexturePool {
public:
    static TexturePool & getInstance();
    TexturePool(const TexturePool&)=delete;
    TexturePool& operator=(const TexturePool&)=delete;
    ~TexturePool();

    static std::shared_ptr<TextureModule> getTextureModule(const std::string & name); // get Texture module

    static std::shared_ptr<TextureModule> loadTexture(std::shared_ptr<TextureModule> & tex_mod); // load external texture for single texture
    static std::shared_ptr<TextureModule> loadInternalTexture(std::shared_ptr<TextureModule> & tex_mod); // load single internal texture

    static void loadBatchedTexture(std::vector<std::shared_ptr<TextureModule>> & textures, const TextureType & type = ColorTexture);  // load batched textures
    static void loadAssetTextures(std::vector<std::shared_ptr<TextureModule>> & textures);
    static void deleteTexure(const std::string & name);  // TODO: !!! 

    static const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & getInternalTextures();
    static const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & getExternalTextures();
    static const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & getAssetTextures();
private:
    TexturePool();

    uint32_t num_of_blocks_;
    std::vector<std::shared_ptr<TextureBlock>> texture_blocks_;   // texture blocks. one texture blocks could hold multiple textures, namely batched textures 
    std::unordered_map<std::string, std::shared_ptr<TextureModule>> texture_;  // all the textures
    std::unordered_map<std::string, std::shared_ptr<TextureModule>> external_tex_; // external textures 
    std::unordered_map<std::string, std::shared_ptr<TextureModule>> internal_tex_; // internal texture for render effects 
    std::unordered_map<std::string, std::shared_ptr<TextureModule>> asset_tex_; // internal texture for render effects 
};

}


#endif //ALICE_ENGINE_TEXTURE_POOL_H
