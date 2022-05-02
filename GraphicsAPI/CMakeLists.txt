project(GRAPHICS_API)

set(GRAPHICS_DIR ${ALICE_RENDERE_DIR}/GraphicsAPI)

option(IS_OPENGL "option for OPENGL API" ON)
if (IS_OPENGL)
    add_definitions(-DIS_OPENGL)
    message("\t---- OPENGL USED -----")

    include_directories(
        ${ALICE_RENDERE_DIR}
        ${ALICE_RENDERE_DIR}/Dependencies/glew/include
    )

    file(GLOB_RECURSE GRAPHIC_SRE ${GRAPHICS_DIR}/opengl/*)
    add_library(${PROJECT_NAME} ${GRAPHIC_SRE})

endif(IS_OPENGL)

message(STATUS "-- GraphicsAPI done")