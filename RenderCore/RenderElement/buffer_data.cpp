//
// Created by HongZh on 2022/05/07, 12:49:08
//

#include "buffer_data.h"

namespace AliceAPI{


BlockBase::BlockBase(){
    
}

DataModule::DataModule(){

}

DataModule::~DataModule(){

}

void DataModule::addInfo(std::shared_ptr<DataInfo<float>> infoF){
    infoF_[infoF->getName()] = infoF;
}

void DataModule::addInfo(std::shared_ptr<DataInfo<uint32_t>> infoUI){
    infoUI_[infoUI->getName()] = infoUI;
}

void DataModule::setIndiceInfo(std::shared_ptr<DataInfo<uint32_t>> indice_info){
    indice_info_ = indice_info;
}

void DataModule::bindDataModule(const std::unordered_map<std::string, VariableInfo> & attribute_list){
    for(auto & [key, info]: infoF_){
        if(attribute_list.find(key) != attribute_list.end()){
            uint32_t loc = attribute_list.at(key).loc_;
            auto block = info->getBlockPtr();
            auto chunk = info->getChunkPtr();
            if(block && chunk){
                block->bindBlock();
                uint64_t offset = info->getOffset() + chunk->getChunkOffset();
                uint32_t span = info->getSpan();
                uint32_t stride = info->getStride();
                block->setLayout(offset, span, stride, loc);
                block->enableVertexAttrib(loc);
                info->setLocation(loc);
            }
        }
    }
    for(auto & [key, info]: infoUI_){
        if(attribute_list.find(key) != attribute_list.end()){
            uint32_t loc = attribute_list.at(key).loc_;
            auto block = info->getBlockPtr();
            auto chunk = info->getChunkPtr();
            if(block && chunk){
                block->bindBlock();
                uint32_t offset = info->getOffset() + chunk->getChunkOffset();
                uint32_t span = info->getSpan();
                uint32_t stride = info->getStride();
                block->setLayout(offset, span, stride, loc);
                block->enableVertexAttrib(loc);
                info->setLocation(loc);
            }
        }
    }
    if(indice_info_){
        auto block = indice_info_->getBlockPtr();
        if(block)
            block->bindBlock();
    }
}

void DataModule::unbindDataModule(){
    for(auto & [key, info]: infoF_){
        uint32_t loc = info->getLocation();
        info->getBlockPtr()->unbindBlock();
        info->getBlockPtr()->disableVertxAttrib(loc);
    }
    for(auto & [key, info]: infoUI_){
        uint32_t loc = info->getLocation();
        info->getBlockPtr()->unbindBlock();
        info->getBlockPtr()->disableVertxAttrib(loc);
    }
    if(indice_info_){
        indice_info_->getBlockPtr()->unbindBlock();
    }
}

}