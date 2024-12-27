function(assert_dir_exists dir)
  if (NOT EXISTS "${dir}")
    message(FATAL_ERROR "directory (${dir}) doesn't exist)")
  endif()
endfunction()

# Symlink assets.
# Symlinking (instead of copying) allows you to change resources and have the
# changes be instantly visible when reloading the game without rebuilding the target
function(symlink_assets target)
  set(GAME_ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")
  assert_dir_exists("${GAME_ASSETS_PATH}")

  add_custom_command(TARGET ${target} POST_BUILD
    COMMENT "Symlink assets to $<TARGET_FILE_DIR:${target}>/assets"
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${GAME_ASSETS_PATH}" "$<TARGET_FILE_DIR:${target}>/assets"
  )
endfunction()
