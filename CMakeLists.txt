cmake_minimum_required(VERSION 3.12)
project(ALICE_RENDER)

set(ALICE_RENDER_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(GRAPHICS_DIR ${ALICE_RENDER_DIR}/GraphicsAPI)
set(CORE_DIR ${ALICE_RENDER_DIR}/RenderCore)

file(GLOB_RECURSE CORE_SRC ${CORE_DIR}/*.cpp)

if(IS_OPENGL)
    message(STATUS " -- OPENGL IS LOADED --")
    file(GLOB GRAPHIC_SRC ${GRAPHICS_DIR}/opengl/*.cpp)

    include_directories(
        ${ALICE_RENDER_DIR}/Dependencies/glew/include
        ${ALICE_RENDER_DIR}/Dependencies/
        ${CORE_DIR}
        ${GRAPHICS_DIR}/opengl
    )

    add_library(
        ${PROJECT_NAME}
        ${GRAPHIC_SRC}
        ${CORE_SRC}
    )

    target_link_libraries(
        ${PROJECT_NAME}
        ${ALICE_RENDER_DIR}/Dependencies/glew/lib/libGLEW.a
    )
endif(IS_OPENGL)

message(STATUS " -- AliceRender done ")
