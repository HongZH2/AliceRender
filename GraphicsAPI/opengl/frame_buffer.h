//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_FRAME_BUFFER_H
#define ALICE_ENGINE_FRAME_BUFFER_H

#include "graphic_predeclared.h"
#include "RenderModules/fbo_mod.h"
#include "texture_2d.h"


namespace AliceAPI {


class FrameBuffer: public FBOModule{
public:
    FrameBuffer();
    FrameBuffer(const FBOInfo & fbo_info);
    ~FrameBuffer();

    // TODO: only one frame buffer for each time
    virtual void createFBO() override;
    virtual void deleteFBO() override;
    virtual void bindFBO() override;
    virtual void unbindFBO() override;
    virtual void drawBuffer(int32_t color_attachment_id) override;
    virtual void readBuffer(int32_t color_attachment_id) override;
    // attachment
    virtual void attachTexture(std::shared_ptr<TextureModule> tex) override;
};

}


#endif //ALICE_ENGINE_FRAME_BUFFER_H
