//
// Created by HongZh on 2022/03/07, 14:48:18
//

#ifndef ALICE_ENGINE_TEXTURE_CUBE_H
#define ALICE_ENGINE_TEXTURE_CUBE_H

#include "graphic_predeclared.h"
#include "texture_2d.h"

namespace AliceAPI {


class TextureCube: public Texture2D{
public:
    TextureCube();
    ~TextureCube();
    virtual void setUpTexture(std::shared_ptr<TextureModule> tex_mod) override;
    virtual void setTextureParams(std::shared_ptr<TextureModule> tex_mod) override;    // set texture parameters
};

}


#endif //ALICE_ENGINE_TEXTURE_CUBE_H