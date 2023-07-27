cmake_minimum_required(VERSION 3.9)
include(FetchContent)
project(skeleton)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -ggdb)

# setting skeleton source
file(GLOB TARGET_SRC "./src/*.cpp" )
include_directories("./include")
add_executable(main ${TARGET_SRC})

# Setting lua54
find_library(
    LUA_LIB
    NAMES lua54 
    HINTS "./libs"
    REQUIRED
)


if (NOT LUA_LIB)
    message(SEND_ERROR "Did not find lib lua54")
else()
    message(STATUS "LUA_LIB: [${LUA_LIB}]")
endif()

# Setting up SDL2
FetchContent_Declare(
        SDL2main
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.x
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL2main)

FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.6.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

# START ADDITION
set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
# END ADDITION
FetchContent_MakeAvailable(SDL2_image)

target_link_libraries(main PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static ${LUA_LIB} ${CMAKE_DL_LIBS})

# Setting up assets file dependency to copy folder
add_custom_command(
  TARGET main
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/assets" "${PROJECT_SOURCE_DIR}/build/assets"
  COMMENT "Copying Assets Bundle"
)

