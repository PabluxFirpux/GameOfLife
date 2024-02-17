cmake_minimum_required(VERSION 3.27)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(GameOfLife
        src/Board.cpp
        src/Board.h
        src/Cell.cpp
        src/Cell.h
        src/MapParser.cpp
        src/MapParser.h
        main.cpp)

install(TARGETS GameOfLife DESTINATION bin)


target_link_libraries(GameOfLife ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(GameOfLife -lopengl32 -lfreeglut)

