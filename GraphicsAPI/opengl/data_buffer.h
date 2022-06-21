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

    virtual void createBuffer(const AE_BUFFER_USEAGE & usage,
                                 const AE_DATA_TYPE & data_t,  
                                 const AE_BUFFER_TYPE & buf_t, 
                                 const uint32_t & size,
                                 void * buffer) override;
    virtual void setUpBuffer(const uint32_t & offset, const uint32_t & size, void* buffer) override;
    
    virtual void copyBuffer(const uint32_t & s_id, const uint32_t & offset = 0) override;
    virtual void deleteBuffer() override;

    virtual void bindBuffer() override;
    virtual void bindBufferRange(const uint32_t & index, const uint32_t & offset, const uint32_t & size) override;
    virtual void unbindBuffer() override;
  
    virtual void enableVAO(const uint32_t & loc) override;    // vertex attribute
    virtual void disableVAO(const uint32_t & loc) override;
    virtual void setUpLayout(const uint64_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc) override;

    #ifdef OPENGL_VERSION3
        virtual void createVertexArray(const uint32_t & n, uint32_t * ids) override;
        virtual void bindVertexArray(const uint32_t & attr_id) override;
        virtual void unbindVertexArray() override;
    #endif // OPENGL_VERSION3
};
}


#endif //ALICE_ENGINE_DATA_BUFFER_H
