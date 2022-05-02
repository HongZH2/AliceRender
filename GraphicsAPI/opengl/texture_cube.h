//
// Created by HongZh on 2022/03/07, 14:48:18
//

#ifndef ALICEENGINE_TEXTURE_CUBE_H
#define ALICEENGINE_TEXTURE_CUBE_H

#include "graphic_predeclared.h"
#include "texture_2d.h"

namespace AliceAPI {


class TextureCube: public Texture2D{
public:
    TextureCube();
    ~TextureCube();
    virtual void setUpTexture() override;
    virtual void setTextureParams(const uint32_t & mod_id) override;    // set texture parameters
};

}


#endif //ALICEENGINE_TEXTURE_CUBE_H