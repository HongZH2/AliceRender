//
// Created by zhanghong50 on 2022/1/19.
//

#include "data_mod.h"
#include "data_buffer.h"
namespace AliceAPI {


template <class T>
DataChunk<T>::DataChunk(){

}

template <class T>
DataChunk<T>::~DataChunk(){

}

template<class T>
DataBlock<T>::DataBlock() {
}

template<class T>
DataBlock<T>::~DataBlock() {

}

template<class T>
std::shared_ptr<DataBlock<T>> DataBlock<T>::getInstancePtr(){
    std::shared_ptr<DataBuffer<T>> block = std::make_shared<DataBuffer<T>>();
    return block;
}

template<class T>
DataInfo<T>::DataInfo(){

}

template<class T>
DataInfo<T>::~DataInfo(){

}

DataModule::DataModule(){

}

DataModule::~DataModule(){

}

void DataModule::bindBuffers(){
    // TODO
}

void DataModule::unbindBuffers(){

}



}
