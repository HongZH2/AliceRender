//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_TEXTURE_MOD_H
#define ALICE_ENGINE_TEXTURE_MOD_H

#include "module_predeclared.h"

namespace AliceAPI {

class TextureInfo;
class TextureBlock;
class TextureModule;

/*
* Texture information for external reference
*/
class TextureInfo{
public:
    uint8_t * buffer_ = nullptr;
    int32_t width_ = 0;
    int32_t height_ = 0;
    int32_t channel_ = 0;
    TextureType type_ = ColorTexture;

    std::string name_;
    std::shared_ptr<TextureInfo> next_ = nullptr;

    TextureInfo();
    TextureInfo(int32_t w, int32_t h, int32_t c, TextureType type);
    ~TextureInfo();
    void releaseBuffer();
};

/*
* Texture Buffer Block
*/
class TextureBlock {
public:
    static std::shared_ptr<TextureBlock> getInstancePtr(const TextureType & type);
    virtual ~TextureBlock();

    virtual void createTexture() = 0;
    virtual void setUpTexture() = 0;
    virtual void deleteTexture(const uint32_t & mod_id) = 0;
    virtual void bindTexture(const uint32_t & mod_id) = 0;
    virtual void unbindTexture(const uint32_t & mod_id) = 0;
    void addTextureModule(const std::shared_ptr<TextureModule> & tex);
protected:
    uint32_t num_tex_ = 0;
    uint32_t * tex_ids_;
    std::vector<std::shared_ptr<TextureModule>> textures_;
    TextureBlock();
};


// Texture Module
class TextureModule: public TextureInfo{
public:
    TextureModule();
    TextureModule(std::shared_ptr<TextureInfo> info);
    ~TextureModule();
    int32_t tex_id_ = -1; // GPU id
    uint32_t mod_id_ = 0;
    AE_TEXTURE_PARAM param_ = AE_CLAMP_TO_BORDER;
    AE_TEXTURE_FILTER filter_ = AE_LINEAR;
    AE_TEXTURE_TYPE interal_type_ = AE_RGBA;
    AE_DATA_TYPE data_t_ = AE_UBYTE;
    AE_TEXTURE_USEAGE usage_ = AE_TEXTURE_2D;
    AE_ATTACHMENT_TYPE attach_type_ = AE_COLOR_ATTACHMENT0;
    std::shared_ptr<TextureBlock> block_; 

    void bindTexture();
    void unbindTexture();
    void deleteTexture();
};

}



#endif //ALICE_ENGINE_TEXTURE_MOD_H
