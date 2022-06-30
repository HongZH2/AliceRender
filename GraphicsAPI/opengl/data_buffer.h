//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_DATA_BUFFER_H
#define ALICE_ENGINE_DATA_BUFFER_H

#include "graphic_predeclared.h"
#include "RenderModules/buffer_mod.h"

namespace AliceAPI {

class DataBuffer: public BufferModule{
public:
    DataBuffer();
    ~DataBuffer();

    void createBuffer(const AE_BUFFER_USEAGE & usage,
                                 const AE_DATA_TYPE & data_t,  
                                 const AE_BUFFER_TYPE & buf_t, 
                                 const uint32_t & size,
                                 void * buffer) override;
    void setUpBuffer(const uint32_t & offset, const uint32_t & size, void* buffer) override;
    
    void copyBuffer(const uint32_t & s_id, const uint32_t & offset = 0) override;
    void deleteBuffer() override;

    void bindBuffer() override;
    void bindBufferRange(const uint32_t & index, const uint32_t & offset, const uint32_t & size) override;
    void unbindBuffer() override;
  
    void enableVAO(const uint32_t & loc) override;    // vertex attribute
    void disableVAO(const uint32_t & loc) override;
    void setUpLayout(const uint64_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc) override;

    #ifdef OPENGL_VERSION3
    void createVertexArray(const uint32_t & n, uint32_t * ids) override;
    void bindVertexArray(const uint32_t & attr_id) override;
    void unbindVertexArray() override;
    #endif // OPENGL_VERSION3
};
}


#endif //ALICE_ENGINE_DATA_BUFFER_H
