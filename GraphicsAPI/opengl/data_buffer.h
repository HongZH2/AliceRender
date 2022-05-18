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
    
    virtual void copyBuffer(std::shared_ptr<BufferModule> buffer) override;
    virtual void deleteBuffer() override;

    virtual void bindBuffer() override;
    virtual void unbindBuffer() override;
  
    virtual void enableVAO(const uint32_t & loc) override;    // vertex attribute
    virtual void disableVAO(const uint32_t & loc) override;
    virtual void setUpLayout(const uint64_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc) override;
};
}


#endif //ALICE_ENGINE_DATA_BUFFER_H
