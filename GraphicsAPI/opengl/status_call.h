
//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_STATUS_CALL_H
#define ALICE_ENGINE_STATUS_CALL_H

#include "graphic_predeclared.h"
#include "RenderModules/status_mod.h"

namespace AliceAPI {


class StatusCall : public StatusModule{
private:
public:
    StatusCall();
    ~StatusCall();

    void enableStatus(const AE_STATUS_TYPE & stype, const int32_t & var) override;
    int32_t checkStatus(const AE_STATUS_TYPE & stype) override;

    void setBlendFunc(const AE_BLEND_FUNC & sfunc, const AE_BLEND_FUNC & dfunc) override;    // set blend function
    void setDepthTestFunc(const AE_DEPTH_TEST_FUNC & func) override;    // set depth function
    
    void clearColorBuffer() override;
    void clearDepthBuffer() override;
    void clearStencilBuffer() override;
    void clearAllBuffer() override;
    void setBufferColor(const GVec4 & color) override;
    void setLineWidth(const float & width) override;
    void viewport(const GVec4i & rect) override;
    GVec4i checkViewport() override;
};

}


#endif //ALICE_ENGINE_STATUS_CALL_H
