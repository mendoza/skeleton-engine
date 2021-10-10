cmake_minimum_required(VERSION 3.9)
project(skeleton)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
add_compile_options(-Wall -ggdb)

file(GLOB TARGET_SRC "./src/*.cpp" )
include_directories("./include")
find_library(LUA_LIB lua53 "./lib/liblua53.a")

find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(main ${TARGET_SRC})
target_link_libraries(main PRIVATE sfml-audio sfml-graphics sfml-window sfml-system ${LUA_LIB} ${CMAKE_DL_LIBS} ${OPENGL_LIBRARIES})