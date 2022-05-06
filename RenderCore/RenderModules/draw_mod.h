//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_DRAW_MOD_H
#define ALICE_ENGINE_DRAW_MOD_H

#include "data_mod.h"

namespace AliceAPI {

class DrawModule {
protected:
    DrawModule();
    virtual void drawElement() = 0;
    virtual void drawArrays() = 0;
    virtual void drawArraysInstance() = 0;
    virtual void drawElementInstance() = 0;
public:
    uint32_t num_vertices_ = 0;
    uint32_t num_instances_ = 0;
    uint32_t offset_ = 0;
    AE_DRAWCALL_USEAGE usage_ = AE_TRIANGLES;
    AE_DRAWCALL_TYPE draw_t_ = AE_DRAW_ELEMENT;
    virtual ~DrawModule();
    virtual void draw();
    static std::shared_ptr<DrawModule> getInstance(uint32_t n_vertices);


};

}



#endif //ALICE_ENGINE_DRAW_MOD_H
