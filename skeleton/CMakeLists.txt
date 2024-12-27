add_subdirectory(third_party)

add_library(skeleton
  # Core
  src/core/Engine.cpp
  src/core/Logger.cpp
  src/core/SceneManager.cpp
  src/core/ResourceManager.cpp
  # DevTools
  # Event
  # ECS
  # Math
  # Graphics
  src/graphics/Renderer.cpp
  # Text
  # Utils
  # Audio
  # UI
  # Game UI
  # Camera
  # Save
  # TileMap
  # GameCommon
)
add_library(skeleton::skeleton ALIAS skeleton)

set_target_properties(skeleton PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)


target_include_directories(skeleton PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# SDL
if(BUILD_SHARED_LIBS)
  target_link_libraries(skeleton PUBLIC
    SDL2::SDL2
  )
else()
  target_link_libraries(skeleton PUBLIC
    SDL2::SDL2-static
  )
endif()

if(WIN32)
  target_link_libraries(skeleton PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(skeleton PUBLIC imgui sol2::sol2 lua::lua)