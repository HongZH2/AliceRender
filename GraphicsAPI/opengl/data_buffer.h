//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICEENGINE_DATA_BUFFER_H
#define ALICEENGINE_DATA_BUFFER_H

#include "graphic_predeclared.h"
#include "RenderModules/data_mod.h"

namespace AliceAPI {

template <class T>
class DataBuffer: public DataBlock<T>{
public:
    DataBuffer();
    ~DataBuffer();

    virtual void createBuffer(const AE_BUFFER_USEAGE & useage, const AE_DATA_TYPE & data_t, const AE_BUFFER_TYPE & buf_t, const uint32_t & capacity) override;
    virtual void resizeBuffer(const uint32_t & capacity);
    virtual void deleteBuffer() override;
    virtual void bindBuffer() override;
    virtual void unbindBuffer() override;
    virtual void setUpBuffer() override;   
    virtual void appendBuffer(std::shared_ptr<DataChunk<T>> & chunk) override; 
    virtual void updateBuffer(const uint32_t & chunk_id) override;
    virtual void enableVAO(const uint32_t & loc) override;    // vertex attribute
    virtual void disableVAO(const uint32_t & loc) override;
    virtual void setUpLayout(const std::shared_ptr<DataInfo<T>> & info, const uint32_t & loc) override; // set VAO
};
}


#endif //ALICEENGINE_DATA_BUFFER_H
