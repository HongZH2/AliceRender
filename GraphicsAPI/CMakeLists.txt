project(GRAPHICS_API)

set(GRAPHICS_DIR ${ALICE_RENDERE_DIR}/GraphicsAPI)
set(CORE_DIR ${ALICE_RENDERE_DIR}/RenderCore)
file(GLOB_RECURSE CORE_SRC ${CORE_DIR}/*.cpp)

option(IS_OPENGL "option for OPENGL API" ON)
if (IS_OPENGL)
    add_definitions(-DIS_OPENGL)
    message("\t---- OPENGL USED -----")

    include_directories(
        ${ALICE_RENDERE_DIR}/Dependencies/glew/include
        ${ALICE_RENDERE_DIR}/Dependencies/
        ${CORE_DIR}
        ${GRAPHICS_DIR}/opengl
    )

    file(GLOB GRAPHIC_SRC ${GRAPHICS_DIR}/opengl/*.cpp)

    add_library(
        ${PROJECT_NAME}
        ${GRAPHIC_SRC}
        ${CORE_SRC}
    )

    target_link_libraries(
        ${PROJECT_NAME}
        ${ALICE_RENDERE_DIR}/Dependencies/glew/lib/libGLEW.dylib
    )
endif(IS_OPENGL)

message(STATUS "-- GraphicsAPI done")