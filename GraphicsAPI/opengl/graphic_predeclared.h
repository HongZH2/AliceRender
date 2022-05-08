//
// Created by zhanghong50 on 2022/1/25.
//

#ifndef ALICE_ENGINE_GRAPHIC_PREDECLARED_H
#define ALICE_ENGINE_GRAPHIC_PREDECLARED_H

#include <string>
#include <map>
#include "GL/glew.h"

namespace AliceAPI {

#define GE_MAX_COMBINED_TEXTURE_IMAGE_UNITS GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
#define GE_MAX_TEXTURE_IMAGE_UNITS GL_MAX_TEXTURE_IMAGE_UNITS

#define AE_DEFINITION(mapFunc)			\
	mapFunc (0, GL_UNSIGNED_BYTE)		\
    mapFunc (1, GL_FLOAT)               \
    mapFunc (2, GL_FLOAT_VEC3)          \
    mapFunc (3, GL_FLOAT_MAT4)          \
    mapFunc (4, GL_SAMPLER_2D)          \
    mapFunc (5, GL_SAMPLER_CUBE)         \
    mapFunc (50, GL_ELEMENT_ARRAY_BUFFER)          \
    mapFunc (51, GL_ARRAY_BUFFER)          \
    mapFunc (100, GL_STATIC_DRAW)          \
    mapFunc (101, GL_DYNAMIC_DRAW)          \
    mapFunc (150, GL_TRIANGLES)          \
    mapFunc (151, GL_POINTS)          \
    mapFunc (152, GL_LINES)          \
    mapFunc (153, GL_LINE_STRIP)          \
    mapFunc (154, GL_TRIANGLE_STRIP)          \
    mapFunc (155, GL_LINE_LOOP)          \
    mapFunc (250, GL_DRAW_ARRAYS_COMMAND_NV)          \
    mapFunc (251, GL_DRAW_ELEMENTS_COMMAND_NV)          \
    mapFunc (252, GL_DRAW_ARRAYS_INSTANCED_COMMAND_NV)  \
    mapFunc (253, GL_DRAW_ELEMENTS_INSTANCED_COMMAND_NV)  \
    mapFunc (300, GL_VERTEX_SHADER)         \
    mapFunc (301, GL_FRAGMENT_SHADER)          \
    mapFunc (302, GL_GEOMETRY_SHADER)       \
    mapFunc (350, GL_TEXTURE_1D)          \
    mapFunc (351, GL_TEXTURE_2D)          \
    mapFunc (352, GL_TEXTURE_3D)          \
    mapFunc (353, GL_TEXTURE_CUBE_MAP)          \
    mapFunc (354, GL_TEXTURE_CUBE_MAP_POSITIVE_X)          \
    mapFunc (355, GL_TEXTURE_CUBE_MAP_POSITIVE_Y)          \
    mapFunc (356, GL_TEXTURE_CUBE_MAP_POSITIVE_Z)          \
    mapFunc (357, GL_TEXTURE_CUBE_MAP_NEGATIVE_X)          \
    mapFunc (358, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)          \
    mapFunc (359, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)          \
    mapFunc (400, GL_REPEAT)          \
    mapFunc (401, GL_CLAMP_TO_EDGE)          \
    mapFunc (402, GL_CLAMP_TO_BORDER)          \
    mapFunc (403, GL_MIRRORED_REPEAT)          \
    mapFunc (404, GL_MIRROR_CLAMP_TO_EDGE)          \
    mapFunc (450, GL_LINEAR)          \
    mapFunc (451, GL_NEAREST)          \
    mapFunc (500, GL_RGB)          \
    mapFunc (501, GL_RGBA)          \
    mapFunc (502, GL_RGBA16F)          \
    mapFunc (503, GL_RGBA32F)          \
    mapFunc (504, GL_DEPTH_COMPONENT)          \
    mapFunc (505, GL_DEPTH_STENCIL)          \
    mapFunc (650, GL_COLOR_ATTACHMENT0)          \
    mapFunc (651, GL_COLOR_ATTACHMENT1)          \
    mapFunc (652, GL_COLOR_ATTACHMENT2)          \
    mapFunc (653, GL_COLOR_ATTACHMENT3)          \
    mapFunc (654, GL_COLOR_ATTACHMENT4)          \
    mapFunc (655, GL_COLOR_ATTACHMENT5)          \
    mapFunc (656, GL_COLOR_ATTACHMENT6)          \
    mapFunc (657, GL_COLOR_ATTACHMENT7)          \
    mapFunc (658, GL_COLOR_ATTACHMENT8)          \
    mapFunc (659, GL_COLOR_ATTACHMENT9)          \
    mapFunc (660, GL_COLOR_ATTACHMENT10)          \
    mapFunc (661, GL_COLOR_ATTACHMENT11)          \
    mapFunc (662, GL_COLOR_ATTACHMENT12)          \
    mapFunc (663, GL_COLOR_ATTACHMENT13)          \
    mapFunc (664, GL_COLOR_ATTACHMENT14)          \
    mapFunc (665, GL_COLOR_ATTACHMENT15)          \
    mapFunc (666, GL_DEPTH_ATTACHMENT)            \
    mapFunc (667, GL_STENCIL_ATTACHMENT)            


#define AE_DEFINITION_MAP(i, t) {i, t},
static std::map<int32_t, uint32_t> GL_DEFS{ AE_DEFINITION(AE_DEFINITION_MAP)};
#undef AE_BUFFER_T_MAP

enum ERROR_CODE{
    SHADER_UPDATE_TEXTURE_ERROR = 0
};


}


#endif //ALICE_ENGINE_GRAPHIC_PREDECLARED_H
