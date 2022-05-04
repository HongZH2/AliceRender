//
// Created by zhanghong50 on 2022/1/28.
//

#include "initialization_mod.h"
#include "complie_predeclared.h"

namespace AliceAPI {


InitModule::InitModule() {

}

std::shared_ptr<InitModule> & InitModule::getInstancePtr() {
    static std::shared_ptr<InitModule> instance_ptr = std::make_shared<InitGraphic>();
    return instance_ptr;
}


InitModule::~InitModule() {

}

}
