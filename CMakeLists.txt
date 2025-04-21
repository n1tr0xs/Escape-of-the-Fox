cmake_minimum_required (VERSION 3.8)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Escape of the Fox")

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

# Add src files
add_executable (Escape-of-the-Fox 
"src/main.cpp" 
"src/Engine.h" "src/Engine.cpp" 
"src/ResourceManager.h" "src/ResourceManager.cpp" 
"src/Entity.h" "src/Entity.cpp" 
"src/Animation.h" "src/Animation.cpp" 
"src/Player.h" "src/Player.cpp" "src/Level.h" "src/Level.cpp"  "src/constants.h" "src/Camera.h" "src/Camera.cpp" "src/Scene.h" "src/GameScene.h" "src/GameScene.cpp" "src/MenuScene.h" "src/MenuScene.cpp")


target_link_libraries(Escape-of-the-Fox SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

# Copy dll files
add_custom_command(TARGET Escape-of-the-Fox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Escape-of-the-Fox> $<TARGET_RUNTIME_DLLS:Escape-of-the-Fox>
  COMMAND_EXPAND_LISTS
)

# Set source and destination directories for assets
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/assets")

# Custom command to copy assets directory
add_custom_command(
    TARGET Escape-of-the-Fox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SOURCE_DIR} ${ASSETS_OUTPUT_DIR}
    COMMENT "Copying assets directory to build folder..."
)
