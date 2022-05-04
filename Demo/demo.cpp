//
// Created by HongZh on 2022/05/04, 21:10:22
//

#include "RenderBuffer/shader_pool.h"
#include <string>

using namespace AliceAPI;

int main(int argc, char ** argv ){
    // initial glew


    // shader
    ShaderInfo shader_info;
    shader_info.name = "test";
    shader_info.vert = 
        "#version 110\n"
        "attribute vec3 pos;\n"
        "void main(){\n"
        "   gl_Position = vec4(pos, 1.0);\n"
        "}\n";
    shader_info.frag = 
        "#version 110\n"
        "void main(){\n"
        "   gl_FragColor = vec4(1.0);\n"
        "}\n";

    ShaderPool::loadShader(shader_info);
    return 0;
}

