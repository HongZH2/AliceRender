//
// Created by zhanghong50 on 2022/2/1.
//

#ifndef ALICE_ENGINE_DATA_POOL_H
#define ALICE_ENGINE_DATA_POOL_H

#include "RenderModules/buffer_mod.h"
#include "RenderElement/buffer_data.h"
#include "entt/entt.hpp"

namespace AliceAPI {

using BlockTypeID = uint64_t;

// BlockType Hash mapping helper function 
template <typename Type, typename Component>
static constexpr BlockTypeID getHashType(){
    constexpr uint32_t dtype = entt::type_hash<Type>();
    constexpr uint32_t ctype = entt::type_hash<Component>();
    return (uint64_t) dtype << 32 | (uint64_t) ctype;
}

/*
* Data Pool for managing the GPU Buffer
*/
class DataPool {
public:
    static DataPool & getInstance();
    ~DataPool();
    DataPool(const DataPool &) = delete;
    DataPool& operator=(const DataPool &) = delete;

    template<typename T, typename Component = void>
    static std::shared_ptr<DataBlock<T>> getBlock(); 

    template<typename T>
    static std::shared_ptr<DataBlock<T>> getUniformBlock(const uint32_t & id);

private:
    uint32_t num_of_block_ = 0;
    uint32_t num_of_uniform_block_ = 0;
    std::unordered_map<BlockTypeID, std::shared_ptr<BlockBase>> blocks_;
    std::vector<std::shared_ptr<BlockBase>> uniform_blocks_;
    DataPool();
};

// Buffer block
template<typename T, typename Component>
std::shared_ptr<DataBlock<T>> DataPool::getBlock(){ // apply for a buffer block 申请一块float block
    DataPool & pool = DataPool::getInstance();
    constexpr BlockTypeID id = getHashType<T, Component>();
    if(pool.blocks_.find(id) != pool.blocks_.end()){
        return std::static_pointer_cast<DataBlock<T>>(pool.blocks_[id]);
    }
    std::shared_ptr<DataBlock<T>> block = std::make_shared<DataBlock<T>>();
    pool.blocks_[id] = block;
    pool.num_of_block_ += 1;
    return block;
}  

// Uniform block
template<typename T>
std::shared_ptr<DataBlock<T>> DataPool::getUniformBlock(const uint32_t & id){
    DataPool & pool = DataPool::getInstance();
    if(id < pool.uniform_blocks_.size()){
        return std::static_pointer_cast<DataBlock<T>>(pool.blocks_[id]);
    }
    std::shared_ptr<DataBlock<T>> block = std::make_shared<DataBlock<T>>();
    pool.uniform_blocks_.emplace_back(block);
    pool.num_of_uniform_block_ += 1;
    return block;
}

}



#endif //ALICE_ENGINE_DATA_POOL_H
