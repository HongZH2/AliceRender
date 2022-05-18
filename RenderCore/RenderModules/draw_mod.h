//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_DRAW_MOD_H
#define ALICE_ENGINE_DRAW_MOD_H

#include "module_predeclared.h"

namespace AliceAPI {



class DrawModule {
public:
    static std::shared_ptr<DrawModule> getInstance(const uint32_t & n_vertices, 
                                                    const AE_DRAWCALL_TYPE & draw_t = AE_DRAW_ELEMENT,
                                                    const AE_DRAWCALL_USEAGE & usage = AE_TRIANGLES,
                                                    const uint32_t & n_instances = 0,
                                                    const uint32_t & offset = 0);
    virtual ~DrawModule();
    virtual void draw();

    void setDrawUsage(const AE_DRAWCALL_USEAGE & usage); // you can change the draw type in the running time
    void setNumOfVertices(const uint32_t & n_vertices);
    void setNumOfInstances(const uint32_t & n_instances);
    void setOffset(const uint32_t & offset);

    const AE_DRAWCALL_TYPE & getDrawType();
protected:
    uint32_t num_vertices_ = 0;
    uint32_t num_instances_ = 0;
    uint64_t offset_ = 0;
    AE_DATA_TYPE data_t_ = AE_UINT;   // indice data
    AE_DRAWCALL_USEAGE usage_ = AE_TRIANGLES;
    AE_DRAWCALL_TYPE draw_t_ = AE_DRAW_ELEMENT;

    DrawModule();
    virtual void drawElement() = 0;
    virtual void drawArrays() = 0;
    virtual void drawArraysInstance() = 0;
    virtual void drawElementInstance() = 0;
};

}



#endif //ALICE_ENGINE_DRAW_MOD_H
