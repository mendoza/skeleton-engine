cmake_minimum_required(VERSION 3.9)
include(FetchContent)
project(skeleton)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS, 1)

# Setting third party deps
# Setting lua54
FetchContent_Declare(
    lua
    GIT_REPOSITORY "https://github.com/marovira/lua"
    GIT_TAG master
)
FetchContent_MakeAvailable(lua)

# Setting Sol2
FetchContent_Declare(
    sol2
    GIT_REPOSITORY "https://github.com/ThePhD/sol2.git"
    GIT_TAG main
)
FetchContent_MakeAvailable(sol2)

# Setting up SDL2
FetchContent_Declare(
        SDL2main
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.x
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
# START ADDITION
set(SDL_TESTS OFF)
# END ADDITION
FetchContent_MakeAvailable(SDL2main)

# Setting up SDL_image
FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.6.x
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

# START ADDITION
set(SDL2IMAGE_INSTALL OFF)
set(SDL2IMAGE_SAMPLES OFF)
set(SDL2IMAGE_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
# END ADDITION
FetchContent_MakeAvailable(SDL2_image)


# setting skeleton source
file(GLOB TARGET_SRC "./src/*.cpp" )
include_directories("./include")
add_executable(${PROJECT_NAME} ${TARGET_SRC})

# Include ImGui using FetchContent
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

# Build ImGui as a static library
add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui.h
  ${imgui_SOURCE_DIR}/imconfig.h
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_internal.h
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imstb_rectpack.h
  ${imgui_SOURCE_DIR}/imstb_textedit.h
  ${imgui_SOURCE_DIR}/imstb_truetype.h
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.h
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
  )

target_compile_features(imgui PUBLIC cxx_std_17)
# Include ImGui's include directory
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
# Specify where to find SDL2 headers
target_include_directories(imgui PRIVATE ${SDL2_SOURCE_DIR}/include)
# Link ImGui with the SDL2 library
target_link_libraries(imgui PRIVATE ${SDL2_LIBRARIES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -ggdb)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static lua::lua sol2::sol2 imgui ${CMAKE_DL_LIBS})

# Setting up assets file dependency to copy folder
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
  COMMENT "Copying Assets Bundle"
)

