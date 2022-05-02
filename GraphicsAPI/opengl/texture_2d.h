//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICEENGINE_TEXTURE_H
#define ALICEENGINE_TEXTURE_H

#include "graphic_predeclared.h"
#include "RenderEngine/RenderModules/texture_mod.h"

namespace AliceAPI {


class Texture2D: public TextureBlock{
public:
    Texture2D();
    virtual ~Texture2D();

    virtual void createTexture() override; 
    virtual void setUpTexture() override;
    virtual void deleteTexture(const uint32_t & mod_id) override;
    virtual void bindTexture(const uint32_t & mod_id) override;
    virtual void unbindTexture(const uint32_t & mod_id) override;

    virtual void setTextureParams(const uint32_t & mod_id);    // set texture parameters
    virtual void setTextureFilter(const uint32_t & mod_id);
  
};

}


#endif //ALICEENGINE_TEXTURE_H
