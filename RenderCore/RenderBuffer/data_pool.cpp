//
// Created by zhanghong50 on 2022/2/1.
//

#include "data_pool.h"

namespace AliceAPI {


DataPool::DataPool() {

}

DataPool::~DataPool() {

}

DataPool & DataPool::getInstance() {
    static DataPool instance;
    return instance;
}

// // TODO
// const std::vector<std::shared_ptr<DataModule>> &
// DataPool::loadData(std::shared_ptr<InstanceMesh> mesh) {

//     std::vector<std::shared_ptr<DataModule>> mesh_data;
//     // vertices
//     const std::vector<float> & vertices = mesh->getVertices();
//     std::shared_ptr<DataModule> vert_data = render_factory.assembleData(vertices);
//     vert_data->setDataLayOut(VERTEX_POSITION);
//     mesh_data.push_back(vert_data);

//     // texture
//     const std::vector<float> & tex_coords = mesh->getTexCoords();
//     if(!tex_coords.empty()){
//         std::shared_ptr<DataModule> tex_data = render_factory.assembleData(tex_coords);
//         tex_data->setDataLayOut(TEXTURE_COORDINATE);
//         mesh_data.push_back(tex_data);
//     }

//     // normals
//     const std::vector<float> & normals = mesh->getNormals();
//     if(!normals.empty()){
//         std::shared_ptr<DataModule> norm_data = render_factory.assembleData(normals);
//         norm_data->setDataLayOut(VERTEX_NORMAL);
//         mesh_data.push_back(norm_data);
//     }

//     // tangents
//     const std::vector<float> & tangents = mesh->getTangents();
//     if(!tangents.empty()){
//         std::shared_ptr<DataModule> tangent_data = render_factory.assembleData(tangents);
//         tangent_data->setDataLayOut(VERTEX_TANGENT);
//         mesh_data.push_back(tangent_data);
//     }

//     // bitangents
//     const std::vector<float> & bitangents = mesh->getBitangents();
//     if(!bitangents.empty()){
//         std::shared_ptr<DataModule> bitangent_data = render_factory.assembleData(bitangents);
//         bitangent_data->setDataLayOut(VERTEX_BITANGENT);
//         mesh_data.push_back(bitangent_data);
//     }

//     // draw indices
//     const std::vector<uint32_t> & draw_indices = mesh->getDrawIndices();
//     std::shared_ptr<DataModule> indices_data = render_factory.assembleData(draw_indices);
//     mesh_data.push_back(indices_data);

//     mesh->setLoaded(true); 

//     switch (mesh->getMeshType()) {
//         case IMPORTED_MODEL:{
//             model_data_pool_[mesh->getMeshName()] = mesh_data;
//             return model_data_pool_.at(mesh->getMeshName());
//         }
//         default:{
//             primitive_data_pool_[mesh->getMeshType()] = mesh_data;
//             return primitive_data_pool_.at(mesh->getMeshType());
//         }
//     }
// }

std::shared_ptr<DataBlock<float>> DataPool::getBlockF(){
    std::shared_ptr<DataBlock<float>> block = DataBlock<float>::getInstancePtr();
    blocksF_.emplace_back(block);
    num_of_blockF_ += 1;
    return block; 
}

std::shared_ptr<DataBlock<uint32_t>> DataPool::getBlockI(){
    std::shared_ptr<DataBlock<uint32_t>> block = DataBlock<uint32_t>::getInstancePtr();
    blocksI_.emplace_back(block);
    num_of_blockI_ += 1;
    return block; 
}

std::shared_ptr<DataBlock<float>> DataPool::queryBlockF(const uint32_t & id){
    if(id < num_of_blockF_)
        return blocksF_[id];
    return nullptr;
}

std::shared_ptr<DataBlock<uint32_t>> DataPool::queryBlockI(const uint32_t & id){
    if(id < num_of_blockI_)
        return blocksI_[id];
    return nullptr;
}

}
