//
// Created by HongZh on 2022/05/07, 12:29:41
//

#ifndef ALICE_ENGINE_DATA_BUFFER_H
#define ALICE_ENGINE_DATA_BUFFER_H

#include "RenderModules/buffer_mod.h"
#include "RenderModules/shader_mod.h"
#include "RenderModules/draw_mod.h"

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
    explicit DataChunk(std::vector<T> & data, uint32_t copy = 1);
    ~DataChunk();

    inline void setChunkOffset(const uint32_t & offset){chunk_offset_ = offset;}
    inline void setChunkID(const int32_t & id){chunk_id_ = id;}
    inline T * & getBuffer(){return buffer_;}
    inline const uint32_t & getChunkOffset(){return chunk_offset_;}
    inline const int32_t & getChunkID(){return chunk_id_;}
    inline const uint32_t & getBufferSize(){return buf_size_;}
private:
    T * buffer_ = nullptr;
    uint32_t buf_size_ = 0;
    uint32_t chunk_offset_ = 0;
    int32_t chunk_id_ = -1;   // sub data block id    
};

/*
*  the construct function will make multiple copies for the input data
*/
template <class T>
DataChunk<T>::DataChunk(std::vector<T> & data, uint32_t copy){
    uint32_t size = data.size();
    buf_size_ = size * copy;
    buffer_ = (T*) malloc(size * copy * sizeof(T));
    for(size_t i = 0; i < copy; ++i){
        memcpy(buffer_ + i * size, &data[0], size * sizeof(T));
    }
}

template <class T>
DataChunk<T>::~DataChunk<T>(){
    if(buffer_)
        free(buffer_);
}

/*
* Class DataInfo: specialy data information for applying data
* 类DataInfo 存储单个data buffer的信息，比如，gpu buffer ID， offset，size 等
*/
template <class T>
class DataInfo {
public:
    DataInfo(std::shared_ptr<DataChunk<T>> start_chunk, 
             std::shared_ptr<DataBlock<T>> block_ptr,
             const std::string & key = "", 
             uint32_t offset = 0, 
             uint32_t stride = 0,
             uint32_t span = 3,
             uint32_t chunk_span = 1);
    ~DataInfo() = default;

    inline const std::string & getName(){return name_;}
    inline const uint32_t & getOffset(){return offset_;}
    inline const uint32_t & getSpan(){return span_;}
    inline const uint32_t & getStride(){return stride_;}
    inline const uint32_t & getChunkSpan(){return chunk_span_;}
    inline const uint32_t & getLocation(){return loc_;}
    inline void setLocation(const uint32_t & loc){loc_ = loc;}
    
    std::shared_ptr<DataChunk<T>> getChunkPtr();
    std::shared_ptr<DataBlock<T>> getBlockPtr();
private:
    uint32_t span_ = 3;  // span of data. For instance, [(x, y, z),...] the span will be 3. 1,2,3,4 will be acceptable.
    uint32_t offset_ = 0;  // local offset of element in the first chunk
    uint32_t stride_ = 0;   // stride, 0 stands for the tightly pack
    uint32_t chunk_span_ = 1;  // chunk span stands for number of chunks that data info describs from the start chunk. 
    uint32_t loc_ = 0; // location in the shaders
    std::string name_;  // key for shader
    std::shared_ptr<DataChunk<T>> start_chunk_; // restore the data block ptr.
    std::weak_ptr<DataBlock<T>> block_ptr_; 
};

template <class T>
DataInfo<T>::DataInfo(std::shared_ptr<DataChunk<T>> start_chunk, 
             std::shared_ptr<DataBlock<T>> block_ptr,
             const std::string & key, 
             uint32_t offset, 
             uint32_t stride,
             uint32_t span,
             uint32_t chunk_span){
    start_chunk_ = start_chunk;
    block_ptr_ = block_ptr;
    name_ = key;
    span_ = span;
    offset_ = offset;
    stride_ = stride;
    chunk_span_ = chunk_span;
}

template <class T>
std::shared_ptr<DataChunk<T>> DataInfo<T>::getChunkPtr(){
    return start_chunk_;
}

template <class T>
std::shared_ptr<DataBlock<T>> DataInfo<T>::getBlockPtr(){
    return block_ptr_.lock();
}

/*
* Data Block a abstract class for buffer opertion
*/
template <class T>
class DataBlock {
public:
    explicit DataBlock(const uint32_t & id);
    virtual ~DataBlock() = default;

    void createBlock(const AE_BUFFER_USEAGE & usage, 
                        const AE_DATA_TYPE & data_t, 
                        const AE_BUFFER_TYPE & draw_t,
                        const uint32_t & capacity = 0,
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


template <class T>
DataBlock<T>::DataBlock(const uint32_t & id): buffer_module_(BufferModule::getInstancePtr()), block_id_(id){
}

template <class T>
void DataBlock<T>::createBlock(const AE_BUFFER_USEAGE &usage, 
                                const AE_DATA_TYPE &data_t, 
                                const AE_BUFFER_TYPE &draw_t, 
                                const uint32_t &capacity, 
                                std::shared_ptr<DataChunk<T>> chunk){
    if(is_allocated_ || capacity  == 0){
        return;
    }
    usage_ = usage;
    data_t_= data_t;
    buf_t_ = draw_t;
    block_capacity_ = capacity;
    if(chunk && chunk->getBufferSize()){
        buffer_module_->createBuffer(usage, data_t, draw_t, capacity * sizeof(T), (void*)chunk->getBuffer());
        chunks_.emplace_back(chunk);
        chunk->setChunkOffset(block_size_);
        chunk->setChunkID(num_of_chunks_);
        block_size_ +=  chunk->getBufferSize();
        num_of_chunks_ += 1;
    }
    else{
        buffer_module_->createBuffer(usage, data_t, draw_t, capacity * sizeof(T), (void*) nullptr);
    }
    is_allocated_ = true;
}

template <class T>
void DataBlock<T>::addChunk(std::shared_ptr<DataChunk<T>> chunk){
    if(!is_allocated_ && block_capacity_ != 0){
        return;
    }
    chunks_.emplace_back(chunk);
    chunk->setChunkOffset(block_size_);
    chunk->setChunkID(num_of_chunks_);
    block_size_ +=  chunk->getBufferSize();
    num_of_chunks_ += 1;
}

template <class T>
void DataBlock<T>::setUpBlock(){
    if(!is_allocated_){
        if(block_capacity_ == 0){
            block_capacity_ = block_size_;
            buffer_module_->createBuffer(usage_, data_t_, buf_t_, block_capacity_* sizeof(T), (void*)nullptr);
            is_allocated_ = true;
        }
        else{
            return;
        }
    }
    for(auto & chunk: chunks_){
       buffer_module_->setUpBuffer(chunk->getChunkOffset(), chunk->getBufferSize() * sizeof(T), chunk->getBuffer());
    }
    is_allocated_ = true;
}

template <class T>
void DataBlock<T>::resizeBlock(const uint32_t & capacity){
    if(!is_allocated_){
        block_capacity_ = capacity;
        return;
    }
    block_capacity_ = capacity;
    std::shared_ptr<BufferModule> new_buffer = BufferModule::getInstancePtr();
    new_buffer->createBuffer(usage_, data_t_, buf_t_, capacity * sizeof(T), (void *)nullptr);
    new_buffer->copyBuffer(buffer_module_);
    buffer_module_ = new_buffer;
}


template <class T>
void DataBlock<T>::updateChunk(std::shared_ptr<DataChunk<T>> chunk){
    if(!is_allocated_ || buf_t_ != AE_DYNAMIC_DRAW || block_capacity_ == 0){  // 不是动态的buffer，不能更新
        return;
    }
    buffer_module_->setUpBuffer(chunk->getChunkOffset(), chunk->getBufferSize() * sizeof(T), chunk->getBuffer());
}

template <class T>
void DataBlock<T>::deleteBlock(){
    if(!is_allocated_){
        return;
    }
    buffer_module_->deleteBuffer();
    num_of_chunks_ = 0;
    block_capacity_= 0;
    block_size_ = 0;
    is_allocated_ = false;
}

template <class T>
void DataBlock<T>::bindBlock(){
    if(!is_allocated_){
        return;
    }
    buffer_module_->bindBuffer();
}

template <class T>
void DataBlock<T>::unbindBlock(){
    if(!is_allocated_){
        return;
    }
    buffer_module_->unbindBuffer();
}

template <class T>
void DataBlock<T>::enableVertexAttrib(const uint32_t & loc){
    if(!is_allocated_){
        return;
    }
    buffer_module_->enableVAO(loc);
}

template <class T>
void DataBlock<T>::disableVertxAttrib(const uint32_t & loc){
    if(!is_allocated_){
        return;
    }
    buffer_module_->disableVAO(loc);
}


template <class T>
void DataBlock<T>::setLayout(const uint32_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc){
    if(!is_allocated_){
        return;
    }
    buffer_module_->setUpLayout(offset * sizeof(T), span, stride * sizeof(T), loc);
}


/*
*  DataModule: batch all the Datainfo for one draw call 
*/

class DataModule{
public:
    DataModule();
    ~DataModule();

    void addInfo(std::shared_ptr<DataInfo<float>> infoF);
    void addInfo(std::shared_ptr<DataInfo<uint32_t>> infoUI);
    void setIndiceInfo(std::shared_ptr<DataInfo<uint32_t>> indice_info);

    void bindDataModule(const std::unordered_map<std::string, VariableInfo> & attribute_list);
    void unbindDataModule();
    
private:
    std::unordered_map<std::string, std::shared_ptr<DataInfo<float>>> infoF_;
    std::unordered_map<std::string, std::shared_ptr<DataInfo<uint32_t>>> infoUI_;
    std::shared_ptr<DataInfo<uint32_t>> indice_info_;
};

}


#endif //ALICE_ENGINE_DATA_BUFFER_H