project(AliceDemo)

set(DEMO_DIR ${ALICE_RENDER_DIR}/Demo)

include_directories(
    ${ALICE_RENDER_DIR}/RenderCore
    ${ALICE_RENDER_DIR}/Dependencies/
    ${DEMO_DIR}/glfw3/include
    ${DEMO_DIR}/imgui/
    ${DEMO_DIR}/imgui/backends/
)

file(GLOB IMGUI_SRC  
${DEMO_DIR}/imgui/*.cpp 
${DEMO_DIR}/imgui/backends/imgui_impl_glfw.cpp
${DEMO_DIR}/imgui/backends/imgui_impl_opengl3.cpp)

add_executable(${PROJECT_NAME} ${ALICE_RENDER_DIR}/Demo/demo.cpp ${IMGUI_SRC})

find_library(OPENGL_LIBRARY OpenGL REQUIRED)
find_library(COCOA_LIBRARY Cocoa REQUIRED)
find_library(IOKIT_LIBRARY IOKit REQUIRED)
find_library(COREVID_LIBRARY CoreVideo REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    GRAPHICS_API
    ${OPENGL_LIBRARY}
    ${COCOA_LIBRARY}
    ${IOKIT_LIBRARY}
    ${COREVID_LIBRARY}
    ${DEMO_DIR}/glfw3/lib/libglfw3.a
)



