//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_GENERAL_INCLUDE_H
#define ALICE_ENGINE_GENERAL_INCLUDE_H

#include <map>
#include <string>
#include "RenderModules/module_predeclared.h"

namespace AliceAPI {


// TODO:
#ifdef __APPLE__
    #define FBO_OFFSET 2.0
#else
    #define FBO_OFFSET 1.0
#endif

enum MeshType{
    NONE_MESH = 0,
    PREDECLARED_PLANE,
    PREDECLARED_CUBE,
    PREDECLARED_SPHERE,
    IMPORTED_MODEL
};

enum ModelType{
    NONE_MODEL = 0,
    MODEL_OBJ,
    MODEL_PLY,
    MODEL_FBX
};

enum LightType{
    NONE_LIGHT = 0,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    LINE_LIGHT,
    AREA_LIGHT,
    FULL_LIGHT
};

enum CameraType{
    NONE_CAMERA = 0,
    ORTHR_CAMERA,
    PINHOLE_CAMERA,
    LENS_CAMERA
};

enum TextureType {
    AssetTexture = -1,
    ColorTexture = 1 << 0,
    NormalTexture = 1 << 1, 
    RoughTexture = 1 << 2,
    BumpTexture = 1 << 3,
    CubeMapTexture = 1 << 4,
    DisplacementTexture = 1 << 5,
    DepthTexture = 1 << 10,
    StencilTexture = 1 << 11,
    ColorDepthTexture = ColorTexture | DepthTexture,
    AllTexture = ColorTexture | DepthTexture | StencilTexture
}; 

static std::map<TextureType, std::string> tex_prefix = {
    {ColorTexture, "ColorTexture"},
    {NormalTexture, "NormalTexture"},
    {BumpTexture, "BumpTexture"},
    {RoughTexture, "RoughTexture"},
    {CubeMapTexture, "CubeMapTexture"},
    {DisplacementTexture, "DisplacementTexture"}
};



}


#endif //ALICE_ENGINE_GENERAL_INCLUDE_H
