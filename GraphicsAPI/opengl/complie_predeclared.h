//
// Created by zhanghong50 on 2022/1/28.
//

#ifndef ALICEENGINE_COMPLIE_PREDECLARED_H
#define ALICEENGINE_COMPLIE_PREDECLARED_H

#include "graphic_predeclared.h"
#include "RenderModules/initialization_mod.h"

namespace AliceAPI {

class InitGraphic: public InitModule{
public:
    InitGraphic();
    ~InitGraphic();
};


}


#endif //ALICEENGINE_COMPLIE_PREDECLARED_H
