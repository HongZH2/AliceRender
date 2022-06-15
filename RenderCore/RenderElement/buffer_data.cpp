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

void DataModule::updateAttributeBuffer(const std::string & key, std::vector<float> & data){
    if(infoF_.find(key) != infoF_.end()){
        auto block = infoF_.at(key)->getBlockPtr();
        auto chunk = infoF_.at(key)->getChunkPtr();
        chunk->updateBuffer(data);
        block->updateChunk(chunk);
    }
}

void DataModule::updateAttributeBuffer(const std::string & key, std::vector<uint32_t> & data){
    if(infoUI_.find(key) != infoUI_.end()){
        auto block = infoUI_.at(key)->getBlockPtr();
        auto chunk = infoUI_.at(key)->getChunkPtr();
        chunk->updateBuffer(data);
        block->updateChunk(chunk);
    }
}

void DataModule::bindDataModule(const std::unordered_map<std::string, VariableInfo> & attribute_list){
    for(auto & [key, info]: infoF_){
        if(attribute_list.find(key) != attribute_list.end()){
            uint32_t loc = attribute_list.at(key).loc_;
            auto block = info->getBlockPtr();
            auto chunk = info->getChunkPtr();
            if(block && chunk){
                #ifdef OPENGL_VERSION3
                    block->bindBlockInfo(info->getAttribID());
                #endif // OPENGL_VERSION3

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
                #ifdef OPENGL_VERSION3
                    block->bindBlockInfo(info->getAttribID());
                #endif // OPENGL_VERSION3

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
        auto block = info->getBlockPtr();
        if(block){
            block->unbindBlock();
            block->disableVertxAttrib(loc);
            #ifdef OPENGL_VERSION3
                block->unbindBlockInfo();
            #endif // OPENGL_VERSION3
        }
    }
    for(auto & [key, info]: infoUI_){
        uint32_t loc = info->getLocation();
        auto block = info->getBlockPtr();
        if(block){
            block->unbindBlock();
            block->disableVertxAttrib(loc);
            #ifdef OPENGL_VERSION3
                block->unbindBlockInfo();
            #endif // OPENGL_VERSION3
        }
    }
    if(indice_info_){
        auto block = indice_info_->getBlockPtr();
        if(block)
            block->unbindBlock();
    }
}



}