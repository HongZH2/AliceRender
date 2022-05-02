//
// Created by zhanghong50 on 2022/1/13.
//

#include "data_buffer.h"

namespace AliceAPI {

template <class T>
DataBuffer<T>::DataBuffer() {

}

template <class T>
DataBuffer<T>::~DataBuffer() {
}

template <class T>
void DataBuffer<T>::setUpBuffer() {
    if(this->buf_id_ != -1){
        bindBuffer();
        // load data by update subdata
        for(auto & data_chunk: this->chunks_){
            glBufferSubData(GL_DEFS[this->usage_], data_chunk->offset_, sizeof(data_chunk->buffer_), &data_chunk->buffer_);
        }
        unbindBuffer();
    }
}


template <class T>
void DataBuffer<T>::setUpLayout(const std::shared_ptr<DataInfo<T>> & info, const uint32_t & loc) {
    enableVAO();
    bindBuffer();
    uint32_t offset = info->chunk_ptr_->chunk_offset_ + info->offset_;
    info->loc_ = loc;
    glVertexAttribPointer(loc, info->span_, GL_DEFS[this->data_t_], false, info->stride_*sizeof(T), (void* )(offset * sizeof(T)));
    unbindBuffer();
    disableVAO();
}

template <class T>
void DataBuffer<T>::createBuffer(const AE_BUFFER_USEAGE & usage, const AE_DATA_TYPE & data_t, const AE_BUFFER_TYPE & buf_t, const uint32_t & capacity) {
    if(!this->is_created_){
        this->usage_= usage;
        this->data_t_= data_t;
        this->buf_t_ = buf_t;
        this->block_capacity_ = capacity;
        glGenBuffers(1, &this->buf_id_);
        glBufferData(GL_DEFS[usage], capacity*sizeof(T), NULL, GL_DEFS[buf_t]);  // prepare the buffer for later use.
        this->is_created_ = true;
    }
}

template <class T>
void DataBuffer<T>::resizeBuffer(const uint32_t & capacity){
    // get a new buffer with the new capacity then copy data to it.
    uint32_t new_buf_id;
    glGenBuffers(1, &new_buf_id);
    glBufferData(GL_DEFS[this->usage_], capacity*sizeof(T), NULL, GL_DEFS[this->buf_t]);  // prepare the buffer for later use.
    glBindBuffer(GL_COPY_READ_BUFFER, this->buf_id_);
    glBindBuffer(GL_COPY_WRITE_BUFFER, new_buf_id);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0,  this->block_capacity_*sizeof(T));
    glDeleteBuffers(1, &this->buf_id_);
    this->block_capacity_ = capacity;
    this->buf_id_ = new_buf_id;
}

template <class T>
void DataBuffer<T>::bindBuffer()  {
    glBindBuffer(GL_DEFS[this->usage_], this->buf_id_);
}

template <class T>
void DataBuffer<T>::unbindBuffer() {
    glBindBuffer(GL_DEFS[this->usage_], 0);
}

template <class T>
void DataBuffer<T>::deleteBuffer() {
    if(this->buf_id_ != -1)
        glDeleteBuffers(1, &this->buf_id_);
}


template <class T>
void DataBuffer<T>::enableVAO(const uint32_t & loc) {
    glEnableVertexAttribArray(loc);
}

template <class T>
void DataBuffer<T>::disableVAO(const uint32_t & loc) {
    glDisableVertexAttribArray(loc);
}

template <class T>
void DataBuffer<T>::appendBuffer(std::shared_ptr<DataChunk<T>> & chunk){
    this->chunks_.emplace_back(chunk);
    chunk->chunk_id_ = this->num_of_chunks_;
    chunk->chunk_offset_ = this->block_size_;
    this->num_of_chunks_ += 1;
    // TODO: if block_size_ > block_capacity_ ??
    this->block_size_ += chunk->buf_size_;
 
    // append buffer
    bindBuffer();
    glBufferSubData(GL_DEFS[this->usage_], chunk->chunk_offset_ * sizeof(T), sizeof(chunk->buffer_), &(chunk->buffer_));
    unbindBuffer();
}
    

template <class T>
void DataBuffer<T>::updateBuffer(const uint32_t & chunk_id){
    if(this->buf_t_ == AE_DYNAMIC_DRAW){  // if it is dynamic.
        auto & cur_chunk = this->chunks[chunk_id];
        bindBuffer();
        glBufferSubData(GL_DEFS[this->usage_], cur_chunk->chunk_offset_ * sizeof(T), sizeof(cur_chunk->buffer_), &(cur_chunk->buffer_));
        unbindBuffer();
    }
}




}
