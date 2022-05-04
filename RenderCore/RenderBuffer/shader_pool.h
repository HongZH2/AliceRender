//
// Created by zhanghong50 on 2022/2/1.
//

#ifndef ALICEENGINE_SHADER_POOL_H
#define ALICEENGINE_SHADER_POOL_H

#include "RenderModules/shader_mod.h"

namespace AliceAPI {


class ShaderPool {
public:
    static ShaderPool & getInstance();
    ShaderPool(const ShaderPool&)=delete;
    ShaderPool& operator=(const ShaderPool&)=delete;
    ~ShaderPool();

    void loadShader(const struct ShaderInfo & shader_info);
    std::shared_ptr<ShaderModule> getShaderModule(const std::string & name);
private:
    std::unordered_map<std::string, std::shared_ptr<ShaderModule>> shader_pool_;
    ShaderPool();

};

}



#endif //ALICEENGINE_SHADER_POOL_H
