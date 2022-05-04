project(AliceDemo)



include_directories(
    ${ALICE_RENDER_DIR}/RenderCore
    ${ALICE_RENDER_DIR}/Dependencies/
)

add_executable(${PROJECT_NAME} ${ALICE_RENDER_DIR}/Demo/demo.cpp)


find_library(OPENGL_LIBRARY OpenGL REQUIRED)
#find_library(COCOA_LIBRARY Cocoa REQUIRED)
#find_library(IOKIT_LIBRARY IOKit REQUIRED)
#find_library(COREVID_LIBRARY CoreVideo REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    GRAPHICS_API
    ${OPENGL_LIBRARY}
#    ${COCOA_LIBRARY}
#    ${IOKIT_LIBRARY}
#    ${COREVID_LIBRARY}
)



