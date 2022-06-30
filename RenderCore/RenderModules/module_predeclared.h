//
// Created by HongZh on 2022/04/21, 14:08:46
//

#ifndef ALICE_ENGINE_MODULE_PREDECLARED_H
#define ALICE_ENGINE_MODULE_PREDECLARED_H

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>
#include "RenderBase/engine_math.h"

namespace AliceAPI {

// FBO
#ifdef __APPLE__
    #define FBO_OFFSET 2.0
#else
    #define FBO_OFFSET 1.0
#endif

#define MAX_NUM_TEXTURE 50


using TextureTypeFlag = uint32_t;
using StatusTypeFlag = uint32_t;

/*
* define Engine API TYPE and USEAGE
* TODO: TO BE EXTENDED
* Note: all the enum type have to own different types of int value
* 所有枚举类型的int值都应该不同 ！！！！！ 
*/

// data Type
enum AE_DATA_TYPE {
    AE_UBYTE = 0,
    AE_BYTE,
    AE_INT,
    AE_UINT,
    AE_SHORT,
    AE_USHORT,
    AE_FLOAT,
    AE_FLOAT_VEC2,
    AE_FLOAT_VEC3,
    AE_FLOAT_MAT3,
    AE_FLOAT_MAT4,
    AE_SAMPLER_2D,
    AE_SAMPLER_CUBE,
};

// buffer type 
enum AE_BUFFER_USEAGE {
    AE_ELEMENT_ARRAY_BUFFER = 50,
    AE_ARRAY_BUFFER,
    AE_UNIFORM_BUFFER
};

// Data Draw
enum AE_BUFFER_TYPE {
    AE_STATIC_DRAW = 100,
    AE_DYNAMIC_DRAW
};

// draw call
enum AE_DRAWCALL_USEAGE {
    AE_TRIANGLES = 150, 
    AE_POINTS, 
    AE_LINES,
    AE_LINE_STRIP,
    AE_TRIANGLE_STRIP,
    AE_LINE_LOOP,
    AE_LINE_ADJACENCY,
    AE_TRIANGLE_ADJACENCY,
    AE_LINE_STRIP_ADJACENCY,
    AE_TRIANGLE_STRIP_ADJACENCY,
    AE_TRIANGLE_FAN
};

enum AE_DRAWCALL_TYPE {
    AE_DRAW_ARRAY = 250,
    AE_DRAW_ELEMENT,
    AE_DRAW_ARRAY_INSTANCE,
    AE_DRAW_ELEMENT_INSTANCE
};

// Shader type
enum AE_SHADER_TYPE {
    AE_VERTEX_SHADER = 300,
    AE_FRAGMENT_SHADER,
    AE_GEOMETRY_SHADER
};


// Texture
enum AE_TEXTURE_USEAGE {
    AE_TEXTURE_1D = 350, 
    AE_TEXTURE_2D, 
    AE_TEXTURE_3D,
    AE_TEXTURE_CUBE,
    AE_TEXTURE_CUBE_POSITIVE_X, 
    AE_TEXTURE_CUBE_POSITIVE_Y,
    AE_TEXTURE_CUBE_POSITIVE_Z ,
    AE_TEXTURE_CUBE_NEGATIVE_X,
    AE_TEXTURE_CUBE_NEGATIVE_Y,
    AE_TEXTURE_CUBE_NEGATIVE_Z
};


enum AE_TEXTURE_PARAM {
    AE_REPEAT = 400,
    AE_CLAMP_TO_EDGE,
    AE_CLAMP_TO_BORDER,
    AE_MIRRORED_REPEAT,
    AE_MIRROR_CLAMP_TO_EDGE
};

enum AE_TEXTURE_FILTER{
    AE_LINEAR = 450,
    AE_NEAREST
};

// texture type
enum AE_TEXTURE_TYPE {
    AE_RGB = 500,
    AE_RGBA,
    AE_RGBA16F,
    AE_RGBA32,
    AE_DEPTH_COMPONENT,
    AE_DEPTH_STENCIL
};


// FrameBuffer
enum AE_ATTACHMENT_TYPE {
    NONE_ATTACHMENT = 649,
    AE_COLOR_ATTACHMENT0 = 650,
    AE_COLOR_ATTACHMENT1,
    AE_COLOR_ATTACHMENT2,
    AE_COLOR_ATTACHMENT3,
    AE_COLOR_ATTACHMENT4,
    AE_COLOR_ATTACHMENT5,
    AE_COLOR_ATTACHMENT6,
    AE_COLOR_ATTACHMENT7,
    AE_COLOR_ATTACHMENT8,
    AE_COLOR_ATTACHMENT9,
    AE_COLOR_ATTACHMENT10,
    AE_COLOR_ATTACHMENT11,
    AE_COLOR_ATTACHMENT12,
    AE_COLOR_ATTACHMENT13,
    AE_COLOR_ATTACHMENT14,
    AE_COLOR_ATTACHMENT15,
    AE_DEPTH_ATTACHMENT,
    AE_STENCIL_ATTACHMENT
};

// status 
enum AE_BLEND_FUNC{
    DISABLE_BLEND = 700,
    AE_ZERO,
    AE_ON,
    AE_SRC_COLOR,
    AE_ONE_MINUS_SRC_COLOR,
    AE_DST_COLOR,
    AE_ONE_MINUS_DST_COLOR,
    AE_SRC_ALPHA,
    AE_ONE_MINUS_SRC_ALPHA,
    AE_DST_ALPHA,
    AE_ONE_MINUS_DST_ALPHA,
    AE_CONSTANT_COLOR,
    AE_ONE_MINUS_CONSTANT_COLOR,
    AE_CONSTANT_ALPHA,
    AE_ONE_MINUS_CONSTANT_ALPHA,
    AE_SRC_ALPHA_SATURATE
};

enum AE_TEST_FUNC{
    AE_NEVER = 716, 
    AE_LESS,
    AE_EQUAL,
    AE_LEQUAL,
    AE_GREATER,
    AE_NOTEQUAL,
    AE_GEQUAL,
    AE_ALWAYS
};

enum AE_POLYGON_MODE_TYPE{
    AE_POINT = 724,
    AE_LINE,
    AE_FILL
};

enum AE_COLOR_BUFFER_MASK{
    AE_COLOR_BUFFER_BIT = 727,
    AE_DEPTH_BUFFER_BIT,
    AE_STENCIL_BUFFER_BIT,
    AE_COLOR_DEPTH_BUFFER_BIT, 
    AE_COLOR_STENCIL_BUFFER_BIT,
    AE_DEPTH_STENCIL_BUFFER_BIT,
    AE_ALL_BUFFER_BIT
};

enum AE_TEST_OPS{
    AE_OPS_KEEP = 734,
    AE_OPS_ZERO,	
    AE_OPS_REPLACE,	
    AE_OPS_INCR,	
    AE_OPS_INCR_WRAP,	
    AE_OPS_DECR,	
    AE_OPS_DECR_WRAP,	
    AE_OPS_INVERT	
};

// status to enable/disable
enum AE_STATUS_TYPE{
    AE_BLEND = 800,
    AE_DEPTH_TEST,
    AE_ALPHA_TEST,
    AE_STENCIL_TEST,
    AE_CULL_FACE,
    AE_POLYGON_MODE,
    AE_PROGRAM_POINT_SIZE
};


/******************************************************************
* Engine defines some defaults uniform keys
*/
enum AttributeKey {
    UNKNOW_KEY = 0x1000,
    VERTEX_POSITION,
    TEXTURE_COORDINATE,
    VERTEX_NORMAL,
    VERTEX_TANGENT,
    VERTEX_BITANGENT
};

enum UniformKey {
    LIGHT_COLOR = 0x2000,
    LIGHT_DIR,
    LIGHT_POSITION,
    CAMERA_VIEW_MAT,
    CAMERA_POSITION,
    CAMERA_ORTHO_MAT,
    CAMERA_PROSPECTIVE_MAT,
    OBJECT_COLOR,
    MODEL_MAT,
    NORM_MAT,
    TEX_LOD
};

enum UniformBlockKey{
    CAMERA_UNIFORMS = 0x3000,
    LIGHT_UNIFORMS, 
    MATERIAL_UNIFORMS
};

static std::unordered_map<uint32_t , std::string> remain_key ={
    {VERTEX_POSITION, "Pos"},
    {TEXTURE_COORDINATE, "UV"},
    {VERTEX_NORMAL, "Norm"},
    {VERTEX_TANGENT, "Tangent"},
    {VERTEX_BITANGENT, "Bitangent"},
    {OBJECT_COLOR, "ObjectColor"},
    {LIGHT_UNIFORMS, "LightUniforms"},
    {LIGHT_POSITION, "LightPos"},
    {LIGHT_COLOR, "LightColor"},
    {LIGHT_DIR, "LightDir"},
    {CAMERA_UNIFORMS, "CameraUniforms"},
    {CAMERA_POSITION, "CameraPos"},
    {CAMERA_VIEW_MAT, "ViewMat"},
    {CAMERA_PROSPECTIVE_MAT, "ProjMat"},
    {MODEL_MAT, "ModelMat"},
    {NORM_MAT, "NormMat"},
    {TEX_LOD, "Lod"},
};

// uniform block binding map // TODO: extended 
static std::unordered_map<uint32_t, uint32_t> uniform_block_bindings = {
    {CAMERA_UNIFORMS, 0},
    {LIGHT_UNIFORMS, 1},
    {MATERIAL_UNIFORMS, 2}
};


}

#endif //ALICE_ENGINE_MODULE_PREDECLARED_H