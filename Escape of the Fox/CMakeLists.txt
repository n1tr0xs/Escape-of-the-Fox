# Add source to this project's executable.
add_executable (Escape-of-the-Fox "main.cpp" "Game.h" "Game.cpp")

find_package(SDL3 REQUIRED)

target_link_libraries(Escape-of-the-Fox SDL3::SDL3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Escape-of-the-Fox PROPERTY CXX_STANDARD 20)
endif()

# Copying dll files
add_custom_command(TARGET Escape-of-the-Fox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Escape-of-the-Fox> $<TARGET_RUNTIME_DLLS:Escape-of-the-Fox>
  COMMAND_EXPAND_LISTS
)