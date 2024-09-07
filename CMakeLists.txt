cmake_minimum_required(VERSION 3.21)

project(
  Skeleton
  VERSION 0.0.1
  LANGUAGES CXX C
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ExeTargetCommon)
include(AssetManagement)

if (WIN32)	
  set(BUILD_SHARED_LIBS OFF CACHE BOOL "Link to libs dynamically")
else()
  set(BUILD_SHARED_LIBS ON CACHE BOOL "Link to libs dynamically")
endif()

# Check that git submodules were cloned
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/skeleton/third_party/SDL/CMakeLists.txt")
  include(FetchSubmodules)
  fetch_submodules()
endif()

add_subdirectory(skeleton)

set(PROJECT_IS_TOP_LEVEL TRUE)
if (PROJECT_IS_TOP_LEVEL)
	add_subdirectory(games)
endif()