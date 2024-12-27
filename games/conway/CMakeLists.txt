cmake_minimum_required(VERSION 3.21)

project(
  conway
  VERSION 0.1.0
  LANGUAGES CXX C)

if(PROJECT_IS_TOP_LEVEL)
  set(SKELETON_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
  add_subdirectory("${SKELETON_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/skeleton")
endif()

add_executable(
  conway
  # src/Level.cpp
  # src/EntityUtil.cpp
  # src/GameComponents.cpp
  # src/GameComponentDisplayers.cpp
  # src/GameDevTools.cpp
  # src/GameEntityInit.cpp
  # src/GameUI.cpp
  src/Game.cpp
  # Scenes
  src/SimulationScene.cpp
  # Nodes
)

target_include_directories(conway PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

set_target_properties(conway PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)

target_include_directories(conway PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

target_link_libraries(conway PRIVATE skeleton::skeleton)

# Assets
symlink_assets(conway)

set_exe_target_common_props(conway)
