//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_DATA_MOD_H
#define ALICE_ENGINE_DATA_MOD_H

#include "module_predeclared.h"

namespace AliceAPI {


class BufferModule{
public:
    static std::shared_ptr<BufferModule> getInstancePtr();
    ~BufferModule();
    virtual void createBuffer(const AE_BUFFER_USEAGE & useage, 
                            const AE_DATA_TYPE & data_t, 
                            const AE_BUFFER_TYPE & buf_t, 
                            const uint32_t & size) = 0;
    virtual void createBuffer(const AE_BUFFER_USEAGE & useage, 
                                const AE_DATA_TYPE & data_t, 
                                const AE_BUFFER_TYPE & buf_t, 
                                const uint32_t & size,
                                float * buffer) = 0;  // create a buffer with size.
    virtual void createBuffer(const AE_BUFFER_USEAGE & useage, 
                            const AE_DATA_TYPE & data_t, 
                            const AE_BUFFER_TYPE & buf_t, 
                            const uint32_t & size,
                            uint32_t * buffer) = 0;  // create a buffer with size.                                               
    virtual void setUpBuffer(const uint32_t & offset, const uint32_t & size, float* buffer) = 0;
    virtual void setUpBuffer(const uint32_t & offset, const uint32_t & size, uint32_t* buffer) = 0;
    
    virtual void copyBuffer(std::shared_ptr<BufferModule> buffer) = 0;
    virtual void deleteBuffer() = 0;
    
    virtual void bindBuffer() = 0;
    virtual void unbindBuffer() = 0;
   
    virtual void enableVAO(const uint32_t & loc) = 0;
    virtual void disableVAO(const uint32_t & loc) = 0; 
    virtual void setUpLayout(const uint32_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc) = 0; // set VAO

    inline const uint32_t & getBufferID(){return buf_id_;}
    inline const uint32_t & getBufferSize(){return buf_size_;}
protected:
    AE_BUFFER_USEAGE usage_;   // useage
    AE_DATA_TYPE data_t_; // data type
    AE_BUFFER_TYPE buf_t_; // buffer type
    uint32_t buf_id_ = 0;
    uint32_t buf_size_ = 0;  // Note: sizeof(type) * len !!!! here
    bool is_allocated_ = false;
    BufferModule();
};

/*
* Data Module: a package of DataBlocks
* TODO: 
*/
class DataModule {
public:
    DataModule();
    ~DataModule();

    void bindBuffers();
    void unbindBuffers();
private:
};

}



#endif //ALICE_ENGINE_DATA_MOD_H