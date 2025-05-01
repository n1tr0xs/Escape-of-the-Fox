cmake_minimum_required (VERSION 3.10)

# Set project name and C++ standard
project ("Escape of the Fox")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the working directory for Visual Studio debugger
if (MSVC)
  set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:Escape-of-the-Fox>")
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Find libraries
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

# Define source files
add_executable(Escape-of-the-Fox
  src/main.cpp
  src/constants.h
  src/Engine.h src/Engine.cpp
  src/ResourceManager.h src/ResourceManager.cpp
  src/Entity.h src/Entity.cpp
  src/Animation.h src/Animation.cpp
  src/Player.h src/Player.cpp
  src/Level.h src/Level.cpp
  src/Camera.h src/Camera.cpp
  src/Scene.h src/Scene.cpp
  src/LevelScene.h src/LevelScene.cpp
  src/MenuScene.h src/MenuScene.cpp
  src/GameCompleteScene.h src/GameCompleteScene.cpp
)

# Link libraries
target_link_libraries(Escape-of-the-Fox 
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)

# Set output directories for different configurations
set_target_properties(Escape-of-the-Fox PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin/Debug
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin/RelWithDebInfo
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy dll files after build
add_custom_command(TARGET Escape-of-the-Fox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Escape-of-the-Fox> $<TARGET_RUNTIME_DLLS:Escape-of-the-Fox>
  COMMAND_EXPAND_LISTS
  COMMENT "Copying SDL runtime DLLs..."
)

# Copy assets directory next to the executable
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")

add_custom_command(TARGET Escape-of-the-Fox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Escape-of-the-Fox>/assets"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SOURCE_DIR}" "$<TARGET_FILE_DIR:Escape-of-the-Fox>/assets"
  COMMENT "Copying assets directory next to executable..."
)
