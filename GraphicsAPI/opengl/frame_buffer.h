//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICEENGINE_FRAME_BUFFER_H
#define ALICEENGINE_FRAME_BUFFER_H

#include "graphic_predeclared.h"
#include "RenderEngine/RenderModules/fbo_mod.h"
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


#endif //ALICEENGINE_FRAME_BUFFER_H
