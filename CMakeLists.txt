cmake_minimum_required(VERSION 3.9)
include(FetchContent)
project(skeleton)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

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

# Setting flecs
FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG        master
)
set(flecs_shared OFF)
FetchContent_MakeAvailable(flecs)
# setting skeleton source
file(GLOB TARGET_SRC "./src/*.cpp" )
include_directories("./include")
add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -ggdb)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static lua::lua sol2::sol2 flecs::flecs_static ${CMAKE_DL_LIBS})

# Setting up assets file dependency to copy folder
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
  COMMENT "Copying Assets Bundle"
)

