//
// Created by zhanghong50 on 2022/1/25.
//

#ifndef ALICE_ENGINE_GRAPHIC_PREDECLARED_H
#define ALICE_ENGINE_GRAPHIC_PREDECLARED_H

#include <string>
#include <map>
#include <unordered_map>
#include "GL/glew.h"

namespace AliceAPI {

#define GE_MAX_COMBINED_TEXTURE_IMAGE_UNITS GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
#define GE_MAX_TEXTURE_IMAGE_UNITS GL_MAX_TEXTURE_IMAGE_UNITS

#define AE_DEFINITION(mapFunc)			\
	mapFunc (0, GL_UNSIGNED_BYTE)		\
    mapFunc (1, GL_BYTE)                \
    mapFunc (2, GL_INT)                 \
    mapFunc (3, GL_UNSIGNED_INT)        \
    mapFunc (4, GL_SHORT)               \
    mapFunc (5, GL_UNSIGNED_SHORT)      \
    mapFunc (6, GL_FLOAT)               \
    mapFunc (7, GL_FLOAT_VEC2)               \
    mapFunc (8, GL_FLOAT_VEC3)          \
    mapFunc (9, GL_FLOAT_MAT3)          \
    mapFunc (10, GL_FLOAT_MAT4)          \
    mapFunc (11, GL_SAMPLER_2D)          \
    mapFunc (12, GL_SAMPLER_CUBE)         \
    mapFunc (50, GL_ELEMENT_ARRAY_BUFFER)  \
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
    mapFunc (667, GL_STENCIL_ATTACHMENT)          \
    mapFunc (701, GL_ZERO)  \
    mapFunc (702, GL_ONE)  \
    mapFunc (703, GL_SRC_COLOR)  \
    mapFunc (704, GL_ONE_MINUS_SRC_COLOR)  \
    mapFunc (705, GL_DST_COLOR)  \
    mapFunc (706, GL_ONE_MINUS_DST_COLOR)  \
    mapFunc (707, GL_SRC_ALPHA)  \
    mapFunc (708, GL_ONE_MINUS_SRC_ALPHA)  \
    mapFunc (709, GL_DST_ALPHA)  \
    mapFunc (710, GL_ONE_MINUS_DST_ALPHA)  \
    mapFunc (711, GL_CONSTANT_COLOR)  \
    mapFunc (712, GL_ONE_MINUS_CONSTANT_COLOR)  \
    mapFunc (713, GL_CONSTANT_ALPHA)  \
    mapFunc (714, GL_ONE_MINUS_CONSTANT_ALPHA)  \
    mapFunc (715, GL_SRC_ALPHA_SATURATE)  \
    mapFunc (800, GL_BLEND)  \
    mapFunc (801, GL_DEPTH_TEST)  \
    mapFunc (802, GL_ALPHA_TEST)  \
    mapFunc (803, GL_STENCIL_TEST)  \
    mapFunc (804, GL_CULL_FACE) \
    mapFunc (805, GL_POLYGON_MODE) \
    mapFunc (716, GL_NEVER) \
    mapFunc (717, GL_LESS) \
    mapFunc (718, GL_EQUAL) \
    mapFunc (719, GL_LEQUAL) \
    mapFunc (720, GL_GREATER) \
    mapFunc (721, GL_NOTEQUAL) \
    mapFunc (722, GL_GEQUAL) \
    mapFunc (723, GL_ALWAYS) \
    mapFunc (724, GL_POINT) \
    mapFunc (725, GL_LINE) \
    mapFunc (726, GL_FILL) \
    mapFunc (727, GL_COLOR_BUFFER_BIT) \
    mapFunc (728, GL_DEPTH_BUFFER_BIT) \
    mapFunc (729, GL_STENCIL_BUFFER_BIT) \
    mapFunc (730, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) \
    mapFunc (731, GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) \
    mapFunc (732, GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) \
    mapFunc (733, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) 

#define AE_DEFINITION_MAP(i, t) {i, t},
static std::unordered_map<int32_t, uint32_t> GL_DEFS{ AE_DEFINITION(AE_DEFINITION_MAP)};
#undef AE_DEFINITION_MAP


#define AE_CAST(mapFunc2)			\
	mapFunc2 (GL_UNSIGNED_BYTE, 0)		\
    mapFunc2 (GL_BYTE, 1)                \
    mapFunc2 (GL_INT, 2)                 \
    mapFunc2 (GL_UNSIGNED_INT, 3)        \
    mapFunc2 (GL_SHORT, 4)               \
    mapFunc2 (GL_UNSIGNED_SHORT, 5)      \
    mapFunc2 (GL_FLOAT, 6)               \
    mapFunc2 (GL_FLOAT_VEC2, 7)          \
    mapFunc2 (GL_FLOAT_VEC3, 8)          \
    mapFunc2 (GL_FLOAT_MAT3, 9)          \
    mapFunc2 (GL_FLOAT_MAT4, 10)          \
    mapFunc2 (GL_SAMPLER_2D, 11)          \
    mapFunc2 (GL_SAMPLER_CUBE, 12)         
          

#define AE_CAST_MAP(i, t) {i, t},
static std::unordered_map<int32_t, uint32_t> GL_CAST{ AE_CAST(AE_CAST_MAP)};
#undef AE_CAST_MAP


enum ERROR_CODE{
    SHADER_UPDATE_TEXTURE_ERROR = 0
};



}



#endif //ALICE_ENGINE_GRAPHIC_PREDECLARED_H
