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
# Disabling what we don't use
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_STB OFF)
set(SDLIMAGE_GIF OFF)
set(SDLIMAGE_JPG OFF)
set(SDLIMAGE_JXL OFF)
set(SDLIMAGE_LBM OFF)
set(SDLIMAGE_PCX OFF)
set(SDLIMAGE_PNM OFF)
set(SDLIMAGE_QOI OFF)
set(SDLIMAGE_SVG OFF)
set(SDLIMAGE_TGA OFF)
set(SDLIMAGE_TIF OFF)
set(SDLIMAGE_WEBP OFF)
set(SDLIMAGE_XCF OFF)
set(SDLIMAGE_XPM OFF)
set(SDLIMAGE_XV OFF)
# Enable what we use
set(SDLIMAGE_PNG ON)
FetchContent_Declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG release-3.2.4
)

# SDL3_ttf
# Disabling what we don't use
set(SDLTTF_HARFBUZZ OFF)
set(SDLTTF_PLUTOSVG OFF)
# Enabling what we use
set(SDLTTF_FREETYPE ON)
FetchContent_Declare(
  SDL3_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG release-3.2.2
)

# SDL3_mixer
# Disabling what we don't use
set(SDLMIXER_OPUS OFF)
set(SDLMIXER_VORBIS OFF)
set(SDLMIXER_FLAC_LIBFLAC OFF)
set(SDLMIXER_GME OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_MOD_XMP OFF)
set(SDLMIXER_MIDI OFF)
set(SDLMIXER_WAVPACK OFF)
set(SDLMIXER_SNDFILE OFF)
# Enabling what we use
set(SDLMIXER_MP3 ON)
FetchContent_Declare(
  SDL3_mixer
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
  GIT_TAG main
)

FetchContent_MakeAvailable(SDL3 SDL3_image SDL3_ttf SDL3_mixer)

# Define source files
add_executable("${PROJECT_NAME}" ${GUI_TYPE}
  # Entry
  "src/main.cpp"

  # Engine and basic components
  "src/constants.hpp"
  "src/smart_SDL.hpp"
  "src/Utils.cpp" "src/Utils.hpp"
  "src/Engine.cpp" "src/Engine.hpp"
  "src/ResourceManager.cpp" "src/ResourceManager.hpp"
  "src/Camera.cpp" "src/Camera.hpp"
  "src/Animation.cpp" "src/Animation.hpp"

  # Game objects
  "src/Entity.cpp" "src/Entity.hpp"
  "src/GameObject.cpp" "src/GameObject.hpp"
  "src/Player.cpp" "src/Player.hpp"

  # Enemies
  "src/Enemy.cpp" "src/Enemy.hpp"
  "src/BeeSwarm.cpp" "src/BeeSwarm.hpp"
  "src/Cock.cpp" "src/Cock.hpp"

  # Scenes and level
  "src/Level.cpp" "src/Level.hpp"
  "src/Scene.hpp"
  "src/LevelScene.cpp" "src/LevelScene.hpp"
  "src/GameCompleteScene.cpp" "src/GameCompleteScene.hpp"
  "src/MenuScene.cpp" "src/MenuScene.hpp"
  "src/MainMenu.cpp" "src/MainMenu.hpp"
  "src/PauseMenu.cpp" "src/PauseMenu.hpp"

  # UI
  "src/MenuButton.cpp" "src/MenuButton.hpp"
  "src/TextLabel.cpp" "src/TextLabel.hpp"
)

if(WIN32)
  # Включить GUI только для Release и RelWithDebInfo, чтобы в Debug была консоль
  set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE $<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>
  )
endif()

# Link libraries
target_link_libraries("${PROJECT_NAME}" PRIVATE 
  SDL3_mixer::SDL3_mixer
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
    "$<TARGET_FILE:SDL3_mixer::SDL3_mixer>"
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