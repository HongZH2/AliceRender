//
// Created by zhanghong50 on 2022/1/28.
//

#ifndef ALICE_ENGINE_COMPLIE_PREDECLARED_H
#define ALICE_ENGINE_COMPLIE_PREDECLARED_H

#include "graphic_predeclared.h"
#include "RenderModules/initialization_mod.h"

namespace AliceAPI {

class InitGraphic: public InitModule{
public:
    InitGraphic();
    ~InitGraphic();
};


}


#endif //ALICE_ENGINE_COMPLIE_PREDECLARED_H
