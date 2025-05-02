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
src/Scene.h
src/LevelScene.h src/LevelScene.cpp
src/MenuScene.h src/MenuScene.cpp
src/GameCompleteScene.h src/GameCompleteScene.cpp
src/GameObject.h src/GameObject.cpp
)

# Set paths to SDL3 SDL3_image SDL3_ttf
set(SDL3_VENDOR_PATH "${CMAKE_SOURCE_DIR}/vendor/SDL3")
set(SDL3_image_VENDOR_PATH "${CMAKE_SOURCE_DIR}/vendor/SDL3_image")
set(SDL3_ttf_VENDOR_PATH "${CMAKE_SOURCE_DIR}/vendor/SDL3_ttf")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)  # x64 architecture
    set(SDL3_LIB_PATH "${SDL3_VENDOR_PATH}/lib/x64")
    set(SDL3_image_LIB_PATH "${SDL3_image_VENDOR_PATH}/lib/x64")
    set(SDL3_ttf_LIB_PATH "${SDL3_ttf_VENDOR_PATH}/lib/x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)  # x86 architecture
    set(SDL3_LIB_PATH "${SDL3_VENDOR_PATH}/lib/x86")
    set(SDL3_image_LIB_PATH "${SDL3_image_VENDOR_PATH}/lib/x86")
    set(SDL3_ttf_LIB_PATH "${SDL3_ttf_VENDOR_PATH}/lib/x86")
else()
    message(FATAL_ERROR "Unsupported architecture")
endif()

# Include and Link SDL3 directory
target_include_directories(Escape-of-the-Fox PRIVATE "${SDL3_VENDOR_PATH}/include")
target_link_directories(Escape-of-the-Fox PRIVATE "${SDL3_LIB_PATH}")
# Include and Link SDL3_image directory
target_include_directories(Escape-of-the-Fox PRIVATE "${SDL3_image_VENDOR_PATH}/include")
target_link_directories(Escape-of-the-Fox PRIVATE "${SDL3_image_LIB_PATH}")
# Include and Link SDL3_ttf directory
target_include_directories(Escape-of-the-Fox PRIVATE "${SDL3_ttf_VENDOR_PATH}/include")
target_link_directories(Escape-of-the-Fox PRIVATE "${SDL3_ttf_LIB_PATH}")
# Link SDL3 SDL3_image SDL3_ttf
target_link_libraries(Escape-of-the-Fox PRIVATE SDL3 SDL3_image SDL3_ttf)

# Set output directories for different configurations
set_target_properties(Escape-of-the-Fox PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin/Debug"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/RelWithDebInfo"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy DLLs after build
set(DLLS_TO_COPY
  "${SDL3_LIB_PATH}/SDL3.dll"
  "${SDL3_image_LIB_PATH}/SDL3_image.dll"
  "${SDL3_ttf_LIB_PATH}/SDL3_ttf.dll"
)
add_custom_command(TARGET Escape-of-the-Fox POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${DLLS_TO_COPY} "$<TARGET_FILE_DIR:Escape-of-the-Fox>"
  COMMAND_EXPAND_LISTS
  COMMENT "Copying SDL3 DLLs to output directory..."
)

# Copy assets after build
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_TARGET_DIR "$<TARGET_FILE_DIR:Escape-of-the-Fox>/assets")
add_custom_command(TARGET Escape-of-the-Fox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_TARGET_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SOURCE_DIR}" "${ASSETS_TARGET_DIR}"
  COMMENT "Copying assets directory next to executable..."
)
