cmake_minimum_required (VERSION 3.10)

# Set project name
project("Escape-of-the-Fox")
set(PROJECT_DISPLAY_NAME "Escape of the Fox")

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the working directory for Visual Studio debugger
if (MSVC)
  set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Fetching libraries
include(FetchContent)

# SDL3
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.10
)

# SDL3_image
set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)
FetchContent_Declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG release-3.2.4
)

# SDL3_ttf
FetchContent_Declare(
  SDL3_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG release-3.2.2
)

FetchContent_MakeAvailable(SDL3 SDL3_image SDL3_ttf)

# Define source files
add_executable("${PROJECT_NAME}"
  "src/main.cpp"
  "src/constants.hpp"
  "src/Engine.hpp" "src/Engine.cpp"
  "src/ResourceManager.hpp" "src/ResourceManager.cpp"
  "src/Entity.hpp" "src/Entity.cpp"
  "src/Animation.hpp" "src/Animation.cpp"
  "src/Player.hpp" "src/Player.cpp"
  "src/Level.hpp" "src/Level.cpp"
  "src/Camera.hpp" "src/Camera.cpp"
  "src/Scene.hpp"
  "src/LevelScene.hpp" "src/LevelScene.cpp"
  "src/MenuButton.hpp" "src/MenuButton.cpp"
  "src/MenuScene.hpp" "src/MenuScene.cpp"
  "src/GameCompleteScene.hpp" "src/GameCompleteScene.cpp"
  "src/GameObject.hpp" "src/GameObject.cpp"
)

# Link libraries
target_link_libraries("${PROJECT_NAME}" PRIVATE 
  SDL3_image::SDL3_image
  SDL3_ttf::SDL3_ttf
  SDL3::SDL3
)

# Set output directories for different configurations
set_target_properties("${PROJECT_NAME}" PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin/Debug"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/RelWithDebInfo"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy SDL3-related DLLs to the output directory after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3::SDL3>"
    "$<TARGET_FILE:SDL3_image::SDL3_image>"
    "$<TARGET_FILE:SDL3_ttf::SDL3_ttf>"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

# Copy assets after build
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_TARGET_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")
add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_TARGET_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SOURCE_DIR}" "${ASSETS_TARGET_DIR}"
  COMMENT "Copying assets directory next to executable..."
)