//
// Created by HongZh on 2022/05/07, 12:49:08
//

#include "buffer_data.h"

namespace AliceAPI{

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


template <class T>
DataInfo<T>::DataInfo(std::shared_ptr<DataChunk<T>> start_chunk, 
             std::shared_ptr<DataBlock<T>> block_ptr,
             const std::string & key, 
             uint32_t span,
             uint32_t offset, 
             uint32_t stride,
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
DataInfo<T>::~DataInfo(){

}

template <class T>
std::shared_ptr<DataChunk<T>> DataInfo<T>::getChunkPtr(){
    return start_chunk_;
}

template <class T>
std::shared_ptr<DataBlock<T>> DataInfo<T>::getBlockPtr(){
    return block_ptr_.lock();
}


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
    if(capacity == 0){
        return;
    }
    block_capacity_ = capacity;
    if(chunk && chunk->getBufferSize()){
        buffer_module_->createBuffer(usage, data_t, draw_t, capacity, chunk->getBuffer());
        chunks_.emplace_back(chunk);
        chunk->setChunkOffset(block_size_);
        chunk->setChunkID(num_of_chunks_);
        block_size_ +=  chunk->getBufferSize();
        num_of_chunks_ += 1;
    }
    else{
        buffer_module_->createBuffer(usage, data_t, draw_t, capacity);
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
            buffer_module_->createBuffer(usage_, data_t_, buf_t_, block_capacity_);
            is_allocated_ = true;
        }
        else{
            return;
        }
    }
    for(auto & chunk: chunks_){
       buffer_module_->setUpBuffer(chunk->getChunkOffset(), chunk->getBufferSize(), chunk->getBuffer());
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
    if(!is_allocated_ || buf_t_ != AE_DYNAMIC_DRAW || block_capacity_ == 0){  // 不是动态的buffer，不能更新
        return;
    }
    buffer_module_->setUpBuffer(chunk->getChunkOffset(), chunk->getBufferSize(), chunk->getBuffer());
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


DataModule::DataModule(){

}

DataModule::~DataModule(){

}

void DataModule::addInfo(std::shared_ptr<DataInfo<float>> infoF){
    infoF_[infoF->getName()] = infoF;
}

void DataModule::addInfo(std::shared_ptr<DataInfo<uint32_t>> infoUI){
    infoUI_[infoUI->getName()] = infoUI;
}

void DataModule::setIndiceInfo(std::shared_ptr<DataInfo<uint32_t>> indice_info){
    indice_info_ = indice_info;
}

void DataModule::setDrawModule(std::shared_ptr<DrawModule> draw_module){
    draw_module_ = draw_module;
}

void DataModule::bindDataModule(const std::unordered_map<std::string, VariableInfo> & attribute_list){
    for(auto & [key, info]: infoF_){
        if(attribute_list.find(key) != attribute_list.end()){
            uint32_t loc = attribute_list.at(key).loc_;
            info->getBlockPtr()->bindBlock();
            uint32_t offset = info->getOffset() + info->getChunkPtr()->getChunkOffset();
            uint32_t span = info->getSpan();
            uint32_t stride = info->getStride();
            info->getBlockPtr()->setLayout(offset, span, stride, loc);
            info->getBlockPtr()->enableVertexAttrib(loc);
            info->setLocation(loc);
        }
    }
    for(auto & [key, info]: infoUI_){
        if(attribute_list.find(key) != attribute_list.end()){
            uint32_t loc = attribute_list.at(key).loc_;
            info->getBlockPtr()->bindBlock();
            uint32_t offset = info->getOffset() + info->getChunkPtr()->getChunkOffset();
            uint32_t span = info->getSpan();
            uint32_t stride = info->getStride();
            info->getBlockPtr()->setLayout(offset, span, stride, loc);
            info->getBlockPtr()->enableVertexAttrib(loc);
            info->setLocation(loc);
        }
    }
    if(indice_info_){
        indice_info_->getBlockPtr()->bindBlock();
    }
}

void DataModule::unbindDataModule(){
    for(auto & [key, info]: infoF_){
        uint32_t loc = info->getLocation();
        info->getBlockPtr()->unbindBlock();
        info->getBlockPtr()->disableVertxAttrib(loc);
    }
    for(auto & [key, info]: infoUI_){
        uint32_t loc = info->getLocation();
        info->getBlockPtr()->unbindBlock();
        info->getBlockPtr()->disableVertxAttrib(loc);
    }
    if(indice_info_){
        indice_info_->getBlockPtr()->unbindBlock();
    }
}

void DataModule::draw(){
    if(!draw_module_){
        return;
    }
    auto draw_t =  draw_module_->getDrawType();
    if(indice_info_ && (draw_t == AE_DRAW_ELEMENT ||  draw_t == AE_DRAW_ELEMENT_INSTANCE)){
        draw_module_->setOffset(indice_info_->getOffset() + indice_info_->getChunkPtr()->getChunkOffset());
    }
    draw_module_->draw();
}

template class DataChunk<float>;
template class DataChunk<uint32_t>;
template class DataInfo<float>;
template class DataInfo<uint32_t>;
template class DataBlock<float>;
template class DataBlock<uint32_t>;

}