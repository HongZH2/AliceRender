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
}
