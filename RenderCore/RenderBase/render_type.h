//
// Created by zhanghong50 on 2022/1/13.
//

#ifndef ALICE_ENGINE_GENERAL_INCLUDE_H
#define ALICE_ENGINE_GENERAL_INCLUDE_H

#include <map>
#include <string>
#include "RenderModules/module_predeclared.h"

namespace AliceAPI {

enum MESH_TYPE{
    UNDEFINED_MESH = 0,
    PREDECLARED_PRITIMIVE = 1 << 0,
    PREDECLARED_PLANE = 1 << 1 | PREDECLARED_PRITIMIVE,
    PREDECLARED_CUBE = 1 << 2 | PREDECLARED_PRITIMIVE,
    PREDECLARED_SPHERE = 1 << 3 | PREDECLARED_PRITIMIVE,
    PREDECLARED_CONE = 1 << 4 | PREDECLARED_PRITIMIVE,
    IMPORTED_MODEL = 1 << 10
};

enum MODELTYPE{
    NONE_MODEL = 0,
    MODEL_OBJ,
    MODEL_PLY,
    MODEL_FBX
};

enum LIGHTTYPE{
    NONE_LIGHT = 0,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    LINE_LIGHT,
    AREA_LIGHT,
    FULL_LIGHT
};

enum CAMERATYPE{
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
    AlbedoTexture = 1 << 12,
    SpecularTexture = 1 << 13 
    // ColNormAlbTexture = ColorTexture | NormalTexture | AlbedoTexture,
    // ColNormAlbSpecTexture = ColorTexture | NormalTexture | AlbedoTexture | SpecularTexture,
    // ColDepTexture = ColorTexture | DepthTexture,
    // DepStenTexture = DepthTexture | StencilTexture, 
    // ColDepStenTexture = ColorTexture | DepthTexture | StencilTexture
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
