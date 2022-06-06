//
// Created by Hong on 2022/2/12.
//

#include "render_parameter.h"

namespace AliceAPI {



RenderParam::RenderParam() {

}

RenderParam::~RenderParam() {

}

void RenderParam::addParam(const TextureType & key, const std::string & tex_name){
    texture_params_[key] = tex_name;
}

}

