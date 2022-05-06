//
// Created by zhanghong50 on 2022/1/28.
//

#ifndef ALICE_ENGINE_INITIALIZATION_MOD_H
#define ALICE_ENGINE_INITIALIZATION_MOD_H

#include "module_predeclared.h"

namespace AliceAPI {


class InitModule {
protected:
    InitModule();
public:
    static std::shared_ptr<InitModule> & getInstancePtr();
    InitModule(const InitModule &) = delete;
    InitModule & operator = (const InitModule &) = delete;
    virtual ~InitModule();
};

}



#endif //ALICE_ENGINE_INITIALIZATION_MOD_H
