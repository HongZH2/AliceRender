//
// Created by HongZh on 2022/05/07, 12:29:41
//

#ifndef ALICE_ENGINE_DATA_BUFFER_H
#define ALICE_ENGINE_DATA_BUFFER_H

#include "RenderModules/data_mod.h"

namespace AliceAPI {

template <class T>
class DataBlock;

template <class T>
class DataChunk;

template <class T>
class DataInfo;

/*
* sub data chunk
* data chunk refers to a chunk of seqential buffer. 
* it can be organised tightly or interlaced
*/
template <class T>
class DataChunk{
public:
    explicit DataChunk(T * buffer, const uint32_t & size){
        buffer_ = buffer;
        buf_size_ = size;
    }
    ~DataChunk() = default;
    T * buffer_ = nullptr; // buffer
    uint32_t buf_size_ = 0;

    inline void setChunkOffset(const uint32_t & offset){chunk_offset_ = offset;}
    inline void setChunkID(const int32_t & id){chunk_id_ = id;}
    inline const uint32_t & getChunkOffset(){return chunk_offset_;}
    inline const int32_t & getChunkID(){return chunk_id_;}
private:
    uint32_t chunk_offset_ = 0;
    int32_t chunk_id_ = -1;   // sub data block id    
};

/*
* Class DataInfo: specialy data information for applying data
* 类DataInfo 存储单个data buffer的信息，比如，gpu buffer ID， offset，size 等
*/
template <class T>
class DataInfo {
public:
    DataInfo(std::shared_ptr<DataChunk<T>> chunk_ptr, 
             std::shared_ptr<DataBlock<T>> block_ptr,
             const std::string & key = "", 
             uint32_t span = 3,
             uint32_t offset = 0, 
             uint32_t stride = 0);
    ~DataInfo();

    std::shared_ptr<DataChunk<T>> getChunkPtr();
    std::shared_ptr<DataBlock<T>> getBlockPtr();
private:
    uint32_t span_ = 3;  // span of data. For instance, [(x, y, z),...] the span will be 3. 1,2,3,4 will be acceptable.
    uint32_t offset_ = 0;  // local offset of element in the chunk
    uint32_t stride_ = 0;   // stride, 0 stands for the tightly pack
    std::string name_;  // key for shader
    std::shared_ptr<DataChunk<T>> chunk_ptr_; // restore the data block ptr.
    std::weak_ptr<DataBlock<T>> block_ptr_; 
};

/*
* Data Block a abstract class for buffer opertion
*/
template <class T>
class DataBlock {
public:
    explicit DataBlock(const uint32_t & id);
    virtual ~DataBlock();

    void createBlock(const AE_BUFFER_USEAGE & usage, 
                        const AE_DATA_TYPE & data_t, 
                        const AE_BUFFER_TYPE & draw_t,
                        const uint32_t & capacity,
                        std::shared_ptr<DataChunk<T>> chunk = nullptr);  // create a datablock with capacity, if the buffer is null, you can fill it later by setUpBlock
    void addChunk(std::shared_ptr<DataChunk<T>> chunk); // attach chunk to Block
    void updateChunk(std::shared_ptr<DataChunk<T>> chunk);
    //void appendBlock(std::shared_ptr<DataChunk<T>> chunk); // after allocating the block, you can still append the block by resizing the block. the performance can't be assured.
    void resizeBlock(const uint32_t &capacity); // resize the Block, the capacity will be modified
    void setUpBlock();  // after attaching the block, you can fill the block by attached chunks automatically
    void deleteBlock(); // clear and delete the block.

    void bindBlock();
    void unbindBlock();
    void enableVertexAttrib(const uint32_t & loc);
    void disableVertxAttrib(const uint32_t & loc);
    void setLayout(const uint32_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc); // set verter pointer

    // query the info of block
    inline const uint32_t & getNumOfChunks(){return num_of_chunks_;}
    inline const uint32_t & getBlockSize(){return block_size_;}
    inline const uint32_t & getBlockCapacity(){return block_capacity_;}
    inline const bool & isAllocated(){return is_allocated_;}

protected:    
    int32_t block_id_ = -1;  // the unique block id in the pool 
    uint32_t block_capacity_ = 0;   // the size of block
    uint32_t block_size_ = 0;
    uint32_t num_of_chunks_ = 0; 
    bool is_allocated_ = false;
    AE_BUFFER_USEAGE usage_ = AE_ARRAY_BUFFER;   // useage
    AE_DATA_TYPE data_t_ = AE_FLOAT; // data type
    AE_BUFFER_TYPE buf_t_ = AE_STATIC_DRAW; // buffer type
    
    std::vector<std::shared_ptr<DataChunk<T>>> chunks_;
    std::shared_ptr<BufferModule> buffer_module_;  // buffer module to do actual operations
};

}


#endif //ALICE_ENGINE_DATA_BUFFER_H