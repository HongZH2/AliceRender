//
// Created by HongZh on 2022/05/07, 12:49:08
//

#include "buffer_data.h"

namespace AliceAPI{

template <class T>
DataInfo<T>::DataInfo(std::shared_ptr<DataChunk<T>> chunk_ptr, 
             std::shared_ptr<DataBlock<T>> block_ptr,
             const std::string & key, 
             uint32_t span,
             uint32_t offset, 
             uint32_t stride){
    chunk_ptr_ = chunk_ptr;
    block_ptr_ = block_ptr;
    name_ = key;
    span_ = span;
    offset_ = offset;
    stride_ = stride;
}

template <class T>
DataInfo<T>::~DataInfo(){

}

template <class T>
std::shared_ptr<DataChunk<T>> DataInfo<T>::getChunkPtr(){
    return chunk_ptr_;
}

template <class T>
std::shared_ptr<DataBlock<T>> DataInfo<T>::getBlockPtr(){
    return block_ptr_.lock();
}

template class DataInfo<float>;
template class DataInfo<uint32_t>;

template <class T>
DataBlock<T>::DataBlock(const uint32_t & id): 
                                            buffer_module_(BufferModule::getInstancePtr()), 
                                            block_id_(id){
}

template <class T>
DataBlock<T>::~DataBlock(){

}

template <class T>
void DataBlock<T>::createBlock(const AE_BUFFER_USEAGE &usage, 
                                const AE_DATA_TYPE &data_t, 
                                const AE_BUFFER_TYPE &draw_t, 
                                const uint32_t &capacity, 
                                std::shared_ptr<DataChunk<T>> chunk){
    if(is_allocated_){
        return;
    }
    usage_ = usage;
    data_t_= data_t;
    buf_t_ = draw_t;
    block_capacity_ = capacity;
    if(chunk && chunk->buffer_){
        buffer_module_->createBuffer(usage, data_t, draw_t, capacity, chunk->buffer_);
        chunks_.emplace_back(chunk);
        chunk->setChunkOffset(block_size_);
        chunk->setChunkID(num_of_chunks_);
        block_size_ +=  chunk->buf_size_;
        num_of_chunks_ += 1;
    }
    else{
        buffer_module_->createBuffer(usage, data_t, draw_t, capacity);
    }
    is_allocated_ = true;
}

template <class T>
void DataBlock<T>::addChunk(std::shared_ptr<DataChunk<T>> chunk){
    if(!is_allocated_){
        return;
    }
    chunks_.emplace_back(chunk);
    chunk->setChunkOffset(block_size_);
    chunk->setChunkID(num_of_chunks_);
    block_size_ +=  chunk->buf_size_;
    num_of_chunks_ += 1;
}

template <class T>
void DataBlock<T>::setUpBlock(){
    if(!is_allocated_){
        return;
    }
    for(auto & chunk: chunks_){
       buffer_module_->setUpBuffer(chunk->getChunkOffset(), chunk->buf_size_, chunk->buffer_);
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
    new_buffer->createBuffer(usage_, data_t_, buf_t_, capacity);
    new_buffer->copyBuffer(buffer_module_);
    buffer_module_ = new_buffer;
}

// template <class T>
// void DataBlock<T>::appendBlock(std::shared_ptr<DataChunk<T>> chunk){
//     if(!is_allocated_){
//         return;
//     }

// }

template <class T>
void DataBlock<T>::updateChunk(std::shared_ptr<DataChunk<T>> chunk){
    if(!is_allocated_ || buf_t_ != AE_DYNAMIC_DRAW){  // 不是动态的buffer，不能更新
        return;
    }
    buffer_module_->setUpBuffer(chunk->getChunkOffset(), chunk->buf_size_, chunk->buffer_);
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
    buffer_module_->setUpLayout(offset, span, stride, loc);
}



template class DataBlock<float>;
template class DataBlock<uint32_t>;
}