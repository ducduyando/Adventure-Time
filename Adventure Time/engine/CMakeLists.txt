cmake_minimum_required(VERSION 3.30)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        Constants.h
        Texture.h
        Texture.cpp
        Character.h
        Character.cpp
        Finn.h
        Finn.cpp
        Skeleton.h
        Skeleton.cpp
        Game.h
        Game.cpp
        Background.h
        Background.cpp
        Menu.h
        Menu.cpp
        Level.h
        Level.cpp
        Warrior.h
        Warrior.cpp
        Ninja.h
        Ninja.cpp
        Music.h
        Music.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC Base SDL3::SDL3)
target_include_directories(${PROJECT_NAME} PUBLIC Base SDL3_image::SDL3_image)
target_include_directories(${PROJECT_NAME} PUBLIC Base SDL3_mixer::SDL3_mixer)



target_link_libraries(${PROJECT_NAME} PUBLIC Base SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PUBLIC Base SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} PUBLIC Base SDL3_mixer::SDL3_mixer)


