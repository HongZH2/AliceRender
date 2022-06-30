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
    explicit FrameBuffer(const FBOInfo & fbo_info);
    ~FrameBuffer();

    // TODO: only one frame buffer for each time
    void createFBO() override;
    void deleteFBO() override;
    void bindFBO() override;
    void unbindFBO() override;
    void drawBuffer(const int32_t & color_attachment_id) override;
    void drawBuffers(const std::vector<uint32_t> & color_attachment_ids) override;
    void readBuffer(const int32_t & color_attachment_id) override;
    // attachment
    void attachTexture(std::shared_ptr<TextureModule> tex) override;
};

}


#endif //ALICE_ENGINE_FRAME_BUFFER_H
