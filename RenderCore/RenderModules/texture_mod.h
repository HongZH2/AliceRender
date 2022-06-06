//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_TEXTURE_MOD_H
#define ALICE_ENGINE_TEXTURE_MOD_H

#include "RenderBase/render_type.h"

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
    TextureInfo(const int32_t & w, const int32_t & h, const int32_t & c, const TextureType & type, const std::string & name);
    ~TextureInfo();
    void releaseBuffer();
};

// Texture Module
class TextureModule: public TextureInfo{
public:
    TextureModule();
    ~TextureModule();
    uint32_t tex_id_ = 0; // GPU id
    uint32_t mod_id_ = 0;

    AE_TEXTURE_PARAM param_ = AE_CLAMP_TO_BORDER;
    AE_TEXTURE_FILTER filter_ = AE_LINEAR;
    AE_TEXTURE_TYPE interal_type_ = AE_RGBA;
    AE_DATA_TYPE data_t_ = AE_UBYTE;
    
    AE_TEXTURE_USEAGE usage_ = AE_TEXTURE_2D;
    AE_ATTACHMENT_TYPE attach_type_ = NONE_ATTACHMENT;
    std::weak_ptr<TextureBlock> block_; 

    void bindTexture();
    void unbindTexture();
    void deleteTexture();
};


/*
*  Texture Buffer Allocator
*/

class TextureAllocator{
public:
    static std::shared_ptr<TextureAllocator> getInstancePtr(const TextureType & type);

    virtual void createTextures(uint32_t * & tex_ids, const uint32_t & num_tex) = 0;
    virtual void setUpTexture(std::shared_ptr<TextureModule> tex_mod) = 0;
    virtual void deleteTexture(uint32_t * tex_ids, const uint32_t & num_tex) =  0;
    virtual void bindTexture(std::shared_ptr<TextureModule> tex_mod) = 0;
    virtual void unbindTexture(std::shared_ptr<TextureModule> tex_mod) = 0;
protected:
    TextureAllocator();
    virtual ~TextureAllocator();
};

/*
* Texture Buffer Block
*/
class TextureBlock {
public:
    TextureBlock(const TextureType & type);
    ~TextureBlock();

    void addTextureModule(const std::shared_ptr<TextureModule> & tex);
    void setUpTexture();

    void bind(uint32_t & mod_id);
    void unbind(uint32_t & mod_id);
    void deleteTexture(uint32_t & mod_id);
    void releaseBlock();
protected:
    uint32_t num_tex_ = 0;
    uint32_t * tex_ids_ = nullptr;
    std::vector<std::shared_ptr<TextureModule>> textures_;
    std::shared_ptr<TextureAllocator> allocator_;    
};



}



#endif //ALICE_ENGINE_TEXTURE_MOD_H
