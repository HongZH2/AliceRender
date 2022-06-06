//
// Created by zhanghong50 on 2022/1/25.
//

#ifndef ALICE_ENGINE_FBO_POOL_H
#define ALICE_ENGINE_FBO_POOL_H



#include "buffer_predeclared.h"
#include "RenderModules/fbo_mod.h"

namespace AliceAPI {


class FBOPool {
public:
    ~FBOPool();
    static FBOPool & getInstance();
    FBOPool(const FBOPool&)=delete;
    FBOPool& operator=(const FBOPool&)=delete;

    static std::shared_ptr<FBOModule> getFBO(const std::string & name);
    static std::shared_ptr<FBOModule> createFBO(FBOInfo & fbo_info);
    static void deleteFBO(const std::string & name);
protected:
    std::unordered_map<std::string, std::shared_ptr<FBOModule>> fbo_pool_;
private:
    FBOPool();
};

}


#endif //ALICE_ENGINE_FBO_POOL_H
