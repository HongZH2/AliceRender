//
// Created by zhanghong50 on 2022/1/13.
//

#include "data_buffer.h"

namespace AliceAPI {

DataBuffer::DataBuffer(){

}

DataBuffer::~DataBuffer(){
    deleteBuffer();
}

void DataBuffer::createBuffer(const AE_BUFFER_USEAGE & usage, 
                            const AE_DATA_TYPE & data_t, 
                            const AE_BUFFER_TYPE & buf_t, 
                            const uint32_t & size){
    if(!is_allocated_){
        glGenBuffers(1, &buf_id_);
        usage_= usage;
        data_t_= data_t;
        buf_t_ = buf_t;
        bindBuffer();
        switch (data_t) {
            case AE_FLOAT:{
                glBufferData(GL_DEFS[usage], size * sizeof(float), NULL, GL_DEFS[buf_t]); 
                buf_size_ = size * sizeof(float);
                is_allocated_ = true;
                break;
            }
            case AE_UBYTE:{
                glBufferData(GL_DEFS[usage], size * sizeof(uint32_t), NULL, GL_DEFS[buf_t]); 
                buf_size_ = size * sizeof(uint32_t);
                is_allocated_ = true;
                break;
            }
            default:
                break;;
        }
        unbindBuffer();
    }
}

void DataBuffer::createBuffer(const AE_BUFFER_USEAGE & usage, 
                                const AE_DATA_TYPE & data_t, 
                                const AE_BUFFER_TYPE & buf_t, 
                                const uint32_t & size,
                                float * buffer) {
    if(!is_allocated_){
        usage_= usage;
        data_t_= data_t;
        buf_t_ = buf_t;
        buf_size_ = size * sizeof(float);
        glGenBuffers(1, &buf_id_);
        bindBuffer();
        glBufferData(GL_DEFS[usage], size * sizeof(float), buffer, GL_DEFS[buf_t]); 
        unbindBuffer();
        is_allocated_ = true;
    }
}

void DataBuffer::createBuffer(const AE_BUFFER_USEAGE & usage, 
                                const AE_DATA_TYPE & data_t, 
                                const AE_BUFFER_TYPE & buf_t, 
                                const uint32_t & size,
                                uint32_t * buffer) {
    if(!is_allocated_){
        usage_= usage;
        data_t_= data_t;
        buf_t_ = buf_t;
        buf_size_ = size * sizeof(uint32_t);
        glGenBuffers(1, &buf_id_);
        bindBuffer();
        glBufferData(GL_DEFS[usage], size * sizeof(uint32_t), buffer, GL_DEFS[buf_t]); 
        unbindBuffer();
        is_allocated_ = true;
    }
}


void DataBuffer::setUpBuffer(const uint32_t & offset, const uint32_t & size, float* buffer) {
    if(is_allocated_){
        bindBuffer();
        // load data by update subdata
        glBufferSubData(GL_DEFS[usage_], offset * sizeof(float), size * sizeof(float), &buffer);
        unbindBuffer();
    }
}

void DataBuffer::setUpBuffer(const uint32_t & offset, const uint32_t & size, uint32_t* buffer) {
    if(is_allocated_){
        bindBuffer();
        // load data by update subdata
        glBufferSubData(GL_DEFS[usage_], offset * sizeof(uint32_t), size * sizeof(uint32_t), &buffer);
        unbindBuffer();
    }
}

void DataBuffer::copyBuffer(std::shared_ptr<BufferModule> buffer){
    if(is_allocated_){
        // get a new buffer with the new capacity then copy data to it.
        glBindBuffer(GL_COPY_READ_BUFFER, buffer->getBufferID());
        glBindBuffer(GL_COPY_WRITE_BUFFER, buf_id_);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, buffer->getBufferSize());
    }
}


void DataBuffer::deleteBuffer() {
    if(is_allocated_)
        glDeleteBuffers(1, &buf_id_);
}

void DataBuffer::bindBuffer()  {
    glBindBuffer(GL_DEFS[usage_], buf_id_);
}


void DataBuffer::unbindBuffer() {
    glBindBuffer(GL_DEFS[usage_], 0);
}

void DataBuffer::setUpLayout(const uint32_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc) {
    bindBuffer();
    switch (data_t_) {
        case AE_FLOAT:{
            glVertexAttribPointer(loc, span, GL_DEFS[data_t_], false, stride * sizeof(float), (void* )(offset * sizeof(float)));
            break;
        }
        case AE_UBYTE:{
            glVertexAttribPointer(loc, span, GL_DEFS[data_t_], false, stride * sizeof(uint32_t), (void* )(offset * sizeof(uint32_t)));
            break;
        }
        default:
            break;
    }
    unbindBuffer();
}




void DataBuffer::enableVAO(const uint32_t & loc) {
    glEnableVertexAttribArray(loc);
}


void DataBuffer::disableVAO(const uint32_t & loc) {
    glDisableVertexAttribArray(loc);
}



}
