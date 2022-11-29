cmake_minimum_required(VERSION 3.9)
project(skeleton)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -ggdb)

file(GLOB TARGET_SRC "./src/*.cpp" )
include_directories("./include")

# Setting lua54
find_library(
    LUA_LIB
    NAMES lua54 
    HINTS "./lib"
    REQUIRED
)

message(STATUS "LUA_LIB: [${LUA_LIB}]")

if (NOT LUA_LIB)
    message(SEND_ERROR "Did not find lib lua54")
endif()

# Setting up SFML
if (NOT LINUX AND WIN32)
    message(STATUS "Building for Windows!")
    set(SFML_DIR "c:/SFML/lib/cmake/SFML")
    set(SFML_DOC_DIR "C:/SFML/doc")
else()
    message(STATUS "Building for Linux!")
endif()

find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)
include_directories(${SFML_INCLUDES})

# Finding OpenGL (IMGUI and SFML)
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDES})

# Linking executable
add_executable(main ${TARGET_SRC})

target_link_libraries(main PRIVATE sfml-audio sfml-graphics sfml-window sfml-system ${LUA_LIB} ${CMAKE_DL_LIBS} ${OPENGL_LIBRARIES})

# Setting up assets file dependency to copy folder
add_custom_target(copy_assets
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

add_dependencies(main copy_assets)

