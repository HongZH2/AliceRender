//
// Created by zhanghong50 on 2022/1/13.
//

#include "frame_buffer.h"


namespace AliceAPI {


// create the default fbo
FrameBuffer::FrameBuffer() {

}

FrameBuffer::FrameBuffer(const FBOInfo & fbo_info) {
    size_ = fbo_info.size_;
    name_ = fbo_info.name_;
    createFBO();  
}

// TODO: texture delete
FrameBuffer::~FrameBuffer() {
    deleteFBO();
}

void FrameBuffer::createFBO() {
    is_available_ = true;
    glGenFramebuffers(1, &f_id_);
}

void FrameBuffer::deleteFBO() {
    if(f_id_ != 0){
        is_available_ = false;
        glDeleteFramebuffers(1, &f_id_);
    }
}

void FrameBuffer::bindFBO() {
    glBindFramebuffer(GL_FRAMEBUFFER, f_id_);
}

void FrameBuffer::unbindFBO() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attachTexture(std::shared_ptr<TextureModule> tex) {
    attached_tex_[tex->type_] = tex->name_;

    switch (tex->usage_) {
        case AE_TEXTURE_2D:{
            bindFBO();
            tex->bindTexture();
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEFS[tex->attach_type_], GL_DEFS[tex->usage_], tex->tex_id_, 0);
            #ifdef DEBUG
                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
                    RenderLog & render_log = RenderLog::getInstance();
                    render_log.submitLog("ERROR::FRAMEBUFFER:: %s is not complete!", name_.c_str());
                }
            #endif // DEBUG
            tex->unbindTexture();
            unbindFBO();
            break;
        }
        default:
            break;
    }

}

void FrameBuffer::drawBuffer(int32_t color_attachment_id){
    bindFBO();
    if(color_attachment_id == -1){
        glDrawBuffer(GL_NONE);
    }
    else{
        glDrawBuffer(GL_COLOR_ATTACHMENT0 + color_attachment_id%GL_MAX_COLOR_ATTACHMENTS);
    }
    unbindFBO();
}

void FrameBuffer::readBuffer(int32_t color_attachment_id){
    bindFBO();
    if(color_attachment_id == -1){
        glReadBuffer(GL_NONE);
    }
    else{
        glReadBuffer(GL_COLOR_ATTACHMENT0 + color_attachment_id%GL_MAX_COLOR_ATTACHMENTS);
    }
    bindFBO();
}



}
