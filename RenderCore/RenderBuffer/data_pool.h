//
// Created by zhanghong50 on 2022/2/1.
//

#ifndef ALICEENGINE_DATA_POOL_H
#define ALICEENGINE_DATA_POOL_H

#include "RenderModules/data_mod.h"

namespace AliceAPI {


class DataPool {
public:
    static DataPool & getInstance();
    ~DataPool();
    DataPool(const DataPool &) = delete;
    DataPool& operator=(const DataPool &) = delete;

    std::shared_ptr<DataBlock<float>> getBlockF();
    std::shared_ptr<DataBlock<uint32_t>> getBlockI();
    std::shared_ptr<DataBlock<float>> queryBlockF(const uint32_t & id);
    std::shared_ptr<DataBlock<uint32_t>> queryBlockI(const uint32_t & id);
private:
    uint32_t num_of_blockF_ = 0;
    uint32_t num_of_blockI_ = 0;
    std::vector<std::shared_ptr<DataBlock<float>>> blocksF_;
    std::vector<std::shared_ptr<DataBlock<uint32_t>>> blocksI_;
    DataPool();
};

}



#endif //ALICEENGINE_DATA_POOL_H
