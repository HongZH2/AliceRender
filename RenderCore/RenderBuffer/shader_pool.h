//
// Created by zhanghong50 on 2022/2/1.
//

#ifndef ALICE_ENGINE_SHADER_POOL_H
#define ALICE_ENGINE_SHADER_POOL_H

#include "RenderModules/shader_mod.h"

namespace AliceAPI {


class ShaderPool {
public:
    static ShaderPool & getInstance();
    ShaderPool(const ShaderPool&)=delete;
    ShaderPool& operator=(const ShaderPool&)=delete;
    ~ShaderPool();

    static void loadShader(const struct ShaderInfo & shader_info);
    static std::shared_ptr<ShaderModule> getShaderModule(const std::string & name);
private:
    std::unordered_map<std::string, std::shared_ptr<ShaderModule>> shader_pool_;
    ShaderPool();

};

}



#endif //ALICE_ENGINE_SHADER_POOL_H
