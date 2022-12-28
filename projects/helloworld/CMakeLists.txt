cmake_minimum_required(VERSION 2.8.4)
project(helloworld)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCE_FILES modplay/*.c *.c)
file(GLOB HEADER_FILES modplay/*.h *.h)

add_executable(helloworld ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(helloworld ${SDL2_LIBRARIES})
