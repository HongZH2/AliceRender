//
// Created by zhanghong50 on 2022/1/19.
//

#include "data_mod.h"
#include "data_buffer.h"
namespace AliceAPI {

BufferModule::BufferModule(){

}

BufferModule::~BufferModule(){
    
}

std::shared_ptr<BufferModule> BufferModule::getInstancePtr(){
    std::shared_ptr<BufferModule> buffer = std::make_shared<DataBuffer>();
    return buffer;
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
