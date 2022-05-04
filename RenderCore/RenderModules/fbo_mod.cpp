//
// Created by zhanghong50 on 2022/1/19.
//

#include "fbo_mod.h"
#include "frame_buffer.h"

namespace AliceAPI {


FBOModule::FBOModule() {
}


FBOModule::~FBOModule() {

}

std::shared_ptr<FBOModule> FBOModule::getInstancePtr(const FBOInfo & fbo_info){
    std::shared_ptr<FrameBuffer> fbo_ptr = std::make_shared<FrameBuffer>(fbo_info);
    return fbo_ptr;
}

const bool & FBOModule::isAvailable(){
    return is_available_;
}

const FBOSize & FBOModule::getFBOSize(){
    return size_;
}


}
