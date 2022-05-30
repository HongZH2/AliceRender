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
                                const uint32_t & size,
                                void * buffer) {
    if(!is_allocated_){
        usage_= usage;
        data_t_= data_t;
        buf_t_ = buf_t;
        buf_size_ = size;
        glGenBuffers(1, &buf_id_);
        bindBuffer();
        glBufferData(GL_DEFS[usage], size, buffer, GL_DEFS[buf_t]); 
        unbindBuffer();
        is_allocated_ = true;
    }
}


void DataBuffer::setUpBuffer(const uint32_t & offset, const uint32_t & size, void* buffer) {
    if(is_allocated_){
        bindBuffer();
        glBufferSubData(GL_DEFS[usage_], offset, size, buffer);        // load data by update subdata
        unbindBuffer();
    }
}


void DataBuffer::copyBuffer(const uint32_t & s_id, const uint32_t & offset){
    if(is_allocated_){
        // get a new buffer with the new capacity then copy data to it.
        // if(GLEW_NV_copy_buffer){
        //     glBindBuffer(GL_COPY_READ_BUFFER, buffer->getBufferID());
        //     glBindBuffer(GL_COPY_WRITE_BUFFER, buf_id_);
        //     glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, buffer->getBufferSize());
        // }  // opengl 2.1 can't not use it

        // get the data from source
        int32_t size;
        glBindBuffer(GL_DEFS[usage_], s_id);
        glGetBufferParameteriv(GL_DEFS[usage_], GL_BUFFER_SIZE, &size);
        char * s_buffer = (char *) malloc(size);
        glGetBufferSubData(GL_DEFS[usage_], 0, size, s_buffer);
        // copy the data to another buffer
        glBindBuffer(GL_DEFS[usage_], buf_id_);
        glBufferSubData(GL_DEFS[usage_], 0, size, (void *)s_buffer);
        glBindBuffer(GL_DEFS[usage_], 0);
        free(s_buffer);
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

void DataBuffer::setUpLayout(const uint64_t & offset, const uint32_t & span, const uint32_t & stride, const uint32_t & loc) {
    glVertexAttribPointer(loc, span, GL_DEFS[data_t_], GL_FALSE, stride, (void*)(offset));
}


void DataBuffer::enableVAO(const uint32_t & loc) {
    glEnableVertexAttribArray(loc);
}


void DataBuffer::disableVAO(const uint32_t & loc) {
    glDisableVertexAttribArray(loc);
}



}
