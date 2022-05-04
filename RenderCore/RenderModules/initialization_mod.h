//
// Created by zhanghong50 on 2022/1/28.
//

#ifndef ALICEENGINE_INITIALIZATION_MOD_H
#define ALICEENGINE_INITIALIZATION_MOD_H

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



#endif //ALICEENGINE_INITIALIZATION_MOD_H
