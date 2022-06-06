//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_FBO_MOD_H
#define ALICE_ENGINE_FBO_MOD_H

#include "texture_mod.h"
#include "module_predeclared.h"

namespace AliceAPI {

struct FBOSize{
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};

struct FBOInfo{
    FBOSize size_;
    std::string name_;
    TextureType tex_t_;
};

class FBOModule {
public:
    static std::shared_ptr<FBOModule> getInstancePtr(const FBOInfo & fbo_info);
    virtual ~FBOModule();

    const bool & isAvailable();
    virtual void createFBO() = 0;
    virtual void deleteFBO() = 0;
    virtual void bindFBO() = 0;
    virtual void unbindFBO() = 0;
    virtual void attachTexture(std::shared_ptr<TextureModule> tex) = 0;
    virtual void drawBuffer(int32_t color_attachment_id) = 0;  // -1 means disable color attachments, color_attrachment
    virtual void readBuffer(int32_t color_attachment_id) = 0;

    const FBOSize & getFBOSize();    
protected:    
    FBOModule();
    FBOSize size_;
    uint32_t f_id_ = 0;
    bool is_available_ = true;
    std::string name_;
    uint32_t num_of_color_attachment_ = 0;
    std::unordered_map<TextureType, std::string> attached_tex_;
};

}


#endif //ALICE_ENGINE_FBO_MOD_H
