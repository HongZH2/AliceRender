//
// Created by zhanghong50 on 2022/2/1.
//

#include "data_pool.h"

namespace AliceAPI {


DataPool::DataPool() {

}

DataPool::~DataPool() {

}

DataPool & DataPool::getInstance() {
    static DataPool instance;
    return instance;
}

std::shared_ptr<DataBlock<float>> DataPool::getBlockF(){
    DataPool & pool = DataPool::getInstance();
    std::shared_ptr<DataBlock<float>> block = std::make_shared<DataBlock<float>>(pool.num_of_blockF_);
    pool.blocksF_.emplace_back(block);
    pool.num_of_blockF_ += 1;
    return block; 
}

std::shared_ptr<DataBlock<uint32_t>> DataPool::getBlockI(){
    DataPool & pool = DataPool::getInstance();
    std::shared_ptr<DataBlock<uint32_t>> block = std::make_shared<DataBlock<uint32_t>>(pool.num_of_blockI_);
    pool.blocksI_.emplace_back(block);
    pool.num_of_blockI_ += 1;
    return block; 
}

std::shared_ptr<DataBlock<float>> DataPool::queryBlockF(const uint32_t & id){
    DataPool & pool = DataPool::getInstance();
    if(id < pool.num_of_blockF_)
        return pool.blocksF_[id];
    return nullptr;
}

std::shared_ptr<DataBlock<uint32_t>> DataPool::queryBlockI(const uint32_t & id){
    DataPool & pool = DataPool::getInstance();
    if(id < pool.num_of_blockI_)
        return pool.blocksI_[id];
    return nullptr;
}

}
