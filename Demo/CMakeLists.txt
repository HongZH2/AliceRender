project(AliceDemo)

set(DEMO_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${ALICE_RENDERE_DIR}/RenderCore
    ${ALICE_RENDERE_DIR}/Dependencies/
)

add_executable(${PROJECT_NAME} demo.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    GRAPHICS_API
)



