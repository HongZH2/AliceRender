//
// Created by zhanghong50 on 2022/2/1.
//

#ifndef ALICE_ENGINE_DATA_POOL_H
#define ALICE_ENGINE_DATA_POOL_H

#include "RenderModules/data_mod.h"
#include "RenderElement/buffer_data.h"

namespace AliceAPI {

// data pool for data block

class DataPool {
public:
    static DataPool & getInstance();
    ~DataPool();
    DataPool(const DataPool &) = delete;
    DataPool& operator=(const DataPool &) = delete;

    // TODO: data pool has two functions: one for data block
    static std::shared_ptr<DataBlock<float>> getBlockF();  // apply for a buffer block 申请一块float block
    static std::shared_ptr<DataBlock<uint32_t>> getBlockI(); // apply for a buffer block 申请一块int block
    static std::shared_ptr<DataBlock<float>> queryBlockF(const uint32_t & id);
    static std::shared_ptr<DataBlock<uint32_t>> queryBlockI(const uint32_t & id);

    // TODO: data pool has two functions: another for data modules
    
private:
    uint32_t num_of_blockF_ = 0;
    uint32_t num_of_blockI_ = 0;
    std::vector<std::shared_ptr<DataBlock<float>>> blocksF_;
    std::vector<std::shared_ptr<DataBlock<uint32_t>>> blocksI_;
    DataPool();
};

}



#endif //ALICE_ENGINE_DATA_POOL_H
