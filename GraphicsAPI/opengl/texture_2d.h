//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_TEXTURE_H
#define ALICE_ENGINE_TEXTURE_H

#include "graphic_predeclared.h"
#include "RenderModules/texture_mod.h"

namespace AliceAPI {


class Texture2D: public TextureAllocator{
public:
    Texture2D();
    virtual ~Texture2D();

    virtual void createTextures(uint32_t * & tex_ids, const uint32_t & num_tex) override;
    virtual void setUpTexture(std::shared_ptr<TextureModule> tex_mod) override;
    virtual void deleteTexture(uint32_t * tex_ids, const uint32_t & num_tex) override;
    virtual void bindTexture(std::shared_ptr<TextureModule> tex_mod) override;
    virtual void unbindTexture(std::shared_ptr<TextureModule> tex_mod) override;

    virtual void setTextureParams(std::shared_ptr<TextureModule> tex_mod);    // set texture parameters
    virtual void setTextureFilter(std::shared_ptr<TextureModule> tex_mod);
  
};

}


#endif //ALICE_ENGINE_TEXTURE_H
