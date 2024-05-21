cmake_minimum_required(VERSION 3.28)
project(Genesis_Cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

if (${PLATFORM} STREQUAL "Desktop")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s -mwindows")
endif()

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} main.cpp
        Application.cpp
        Application.h
        Application.cpp
        Application.h
        Graphics/Renderer.cpp
        Graphics/Renderer.h
        Random.h
        Level/Level.cpp
        Level/Level.h
        Graphics/SpriteSheet.cpp
        Graphics/SpriteSheet.h
        Graphics/Sprite.cpp
        Graphics/Sprite.h
        Core/Assert.h
        gpch.h
        Game.cpp
        Game.h
        Graphics/ImageUtils.cpp
        Graphics/ImageUtils.h
        Entity/Entity.cpp
        Entity/Entity.h
        Entity/Mob.cpp
        Entity/Mob.h
        Entity/Player.cpp
        Entity/Player.h
        Level/Tile.cpp
        Level/Tile.h
        Entity/Female.cpp
        Entity/Female.h
        Entity/ForestMob.cpp
        Entity/ForestMob.h
        Level/Population.cpp
        Level/Population.h
        Menu/Menu.h
        Menu/MainMenu.cpp
        Menu/MainMenu.h
        Menu/HelpMenu.cpp
        Menu/HelpMenu.h
        Menu/AboutMenu.cpp
        Menu/AboutMenu.h
        Menu/GameOverMenu.cpp
        Menu/GameOverMenu.h
        Sound/Sound.cpp
        Sound/Sound.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_precompile_headers(${PROJECT_NAME} PUBLIC gpch.h)

if (${PLATFORM} STREQUAL "Desktop")
    target_sources(${PROJECT_NAME} PRIVATE res/app.rc)
endif()

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 --preload-file ../res")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()