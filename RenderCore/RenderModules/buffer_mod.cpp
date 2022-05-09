//
// Created by zhanghong50 on 2022/1/19.
//

#include "buffer_mod.h"
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


}
