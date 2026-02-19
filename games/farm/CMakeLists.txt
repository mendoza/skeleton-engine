cmake_minimum_required(VERSION 3.21)

project(farm VERSION 0.1.0 LANGUAGES CXX C)

if(PROJECT_IS_TOP_LEVEL)
  set(SKELETON_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
  add_subdirectory("${SKELETON_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/skeleton")
endif()

add_executable(farm
  src/Game.cpp
  src/FarmScene.cpp
)

set_target_properties(farm PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)
target_include_directories(farm PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
target_link_libraries(farm PRIVATE skeleton::skeleton)

symlink_assets(farm)
set_exe_target_common_props(farm)
