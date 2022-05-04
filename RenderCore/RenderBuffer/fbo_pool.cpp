//
// Created by zhanghong50 on 2022/1/25.
//

#include "fbo_pool.h"
#include "RenderModules/fbo_mod.h"

namespace AliceAPI {

FBOPool::FBOPool() {

}

FBOPool::~FBOPool() {

}

FBOPool & FBOPool::getInstance() {
    static FBOPool fbo_pool_;
    return fbo_pool_;
}

std::shared_ptr<FBOModule>FBOPool::getFBO(const std::string & name){
    if(fbo_pool_.find(name) != fbo_pool_.end()){
        return fbo_pool_[name];
    }
    return nullptr;
}

std::shared_ptr<FBOModule> FBOPool::createFBO(FBOInfo & fbo_info){
    if(fbo_pool_.find(fbo_info.name_) != fbo_pool_.end()){
        deleteFBO(fbo_info.name_);
    }

    // fix the size of fbo for macos
    fbo_info.size_.width_ *= FBO_OFFSET;
    fbo_info.size_.height_ *= FBO_OFFSET;
    
    std::shared_ptr<FBOModule> fbo =  FBOModule::getInstancePtr(fbo_info);
    fbo_pool_[fbo_info.name_] = fbo;
    return fbo_pool_[fbo_info.name_];
}

void FBOPool::deleteFBO(const std::string & name) {
    fbo_pool_[name]->deleteFBO();
}


}
