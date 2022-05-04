//
// Created by zhanghong50 on 2022/1/26.
//

#ifndef ALICEENGINE_DRAW_CALL_H
#define ALICEENGINE_DRAW_CALL_H

#include "graphic_predeclared.h"
#include "RenderModules/draw_mod.h"

namespace AliceAPI {


class DrawCall: public DrawModule {
public:
    DrawCall();
    DrawCall(uint32_t n_vertices);
    ~DrawCall();

    virtual void drawElement() override;
    virtual void drawArrays() override;
    virtual void drawArraysInstance() override;
    virtual void drawElementInstance() override;
};

}



#endif //ALICEENGINE_DRAW_CALL_H
