cmake_minimum_required(VERSION 3.1.5)

project(snake)

add_executable(snake main.cpp Fruit.cpp Game.cpp GameOverScreen.cpp GameScreen.cpp MenuScreen.cpp Screen.cpp Snake.cpp SnakeNode.cpp)


target_include_directories(snake PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(snake PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(snake PRIVATE sfml-audio-d sfml-graphics-d sfml-network-d sfml-system-d sfml-window-d)

target_compile_options(snake PRIVATE -O3 -std=c++20)
