//
// Created by zhanghong50 on 2022/1/19.
//

#ifndef ALICE_ENGINE_DATA_MOD_H
#define ALICE_ENGINE_DATA_MOD_H

#include "module_predeclared.h"

namespace AliceAPI {

template <class T>
class DataBlock;

template <class T>
class DataChunk;

template <class T>
class DataInfo;

class DataModule;

/*
* sub data chunk
* data chunk refers to a chunk of seqential buffer. 
* it can be organised tightly or interlaced
*/
template <class T>
class DataChunk{
public:
    DataChunk();
    ~DataChunk();
    T * buffer_ = nullptr; // buffer
    uint32_t buf_size_ = 0;
    uint32_t chunk_offset_ = 0;
    int32_t chunk_id_ = -1;   // sub data block id
    std::shared_ptr<DataBlock<T>> block_ptr_; //  which buffer block it belongs to 
};

/*
* Class DataInfo: specialy data information for applying data
* 类DataInfo 存储单个data buffer的信息，比如，gpu buffer ID， offset，size 等
*/
template <class T>
class DataInfo {
public:
    DataInfo();
    ~DataInfo();
    int32_t loc_ = -1; // loc in the shader
    uint32_t span_ = 3;  // span of data. For instance, [(x, y, z),...] the span will be 3. 1,2,3,4 will be acceptable.
    uint32_t size_ = 0; // the size of element. the size of buffer
    uint32_t offset_ = 0;  // local offset of element in the chunk
    uint32_t stride_ = 0;   // stride
    std::string name_;  // name 
    std::string key_;  // variable name in shader
    std::shared_ptr<DataChunk<T>> chunk_ptr_; 
};

/*
* Data Block a abstract class for buffer opertion
*/
template <class T>
class DataBlock {
public:
    static std::shared_ptr<DataBlock> getInstancePtr();
    virtual ~DataBlock();
    
    virtual void createBuffer(const AE_BUFFER_USEAGE & useage, const AE_DATA_TYPE & data_t, const AE_BUFFER_TYPE & buf_t, const uint32_t & capacity) = 0;  // create a buffer with size.
    virtual void resizeBuffer(const uint32_t & capacity) = 0;
    virtual void deleteBuffer() = 0;
    virtual void bindBuffer() = 0;
    virtual void unbindBuffer() = 0;
    virtual void appendBuffer(std::shared_ptr<DataChunk<T>> & chunk) = 0; // append data Chunk
    virtual void updateBuffer(const uint32_t & chunk_id) = 0;   // update
    virtual void enableVAO(const uint32_t & loc) = 0;
    virtual void disableVAO(const uint32_t & loc) = 0; 
    virtual void setUpLayout(const std::shared_ptr<DataInfo<T>> & info, const uint32_t & loc) = 0; // set VAO with location in the shader

protected:    
    uint32_t block_capacity_ = 0;   // the size of block
    uint32_t block_size_ = 0;
    uint32_t num_of_chunks_ = 0; 
    int32_t buf_id_ = -1;  // GPU ID
    bool is_created_ = false;
    AE_BUFFER_USEAGE usage_ = AE_ARRAY_BUFFER;   // useage
    AE_DATA_TYPE data_t_ = AE_FLOAT; // data type
    AE_BUFFER_TYPE buf_t_ = AE_STATIC_DRAW; // buffer type
    
    std::vector<std::shared_ptr<DataChunk<T>>> chunks_;
    DataBlock();
};

/*
* Data Module: a package of DataBlocks
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
