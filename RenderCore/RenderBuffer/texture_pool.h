//
// Created by zhanghong50 on 2022/1/26.
//

#ifndef ALICEENGINE_TEXTURE_POOL_H
#define ALICEENGINE_TEXTURE_POOL_H

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

    std::shared_ptr<TextureModule> getTextureModule(const std::string & name); // get Texture module

    void loadTexture(std::shared_ptr<TextureInfo> & tex_info); // load external texture for single texture
    void loadInternalTexture(std::shared_ptr<TextureInfo> & tex_info); // load single internal texture
    void loadBatchedTexture(std::vector<std::shared_ptr<TextureInfo>> & textures);  // load batched textures
    void deleteTexure(const std::string & name);  // TODO: !!! 

    const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & getInternalTextures();
    const std::unordered_map<std::string, std::shared_ptr<TextureModule>> & getExternalTextures();
private:
    TexturePool();

    uint32_t num_of_blocks_;
    std::vector<std::shared_ptr<TextureBlock>> texture_blocks_;   // texture blocks. one texture blocks could hold multiple textures, namely batched textures 
    std::unordered_map<std::string, std::shared_ptr<TextureModule>> texture_;  // all the textures
    std::unordered_map<std::string, std::shared_ptr<TextureModule>> external_tex_; // external textures 
    std::unordered_map<std::string, std::shared_ptr<TextureModule>> internal_tex_; // internal texture for render effects 
};

}


#endif //ALICEENGINE_TEXTURE_POOL_H
