# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.24.4)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(/opt/homebrew/opt/sdl2_ttf/include/SDL2/)

# project name
project(pong)

# creates the variable EXEC and sets it to hello
set(EXEC pong)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# I../includes
include_directories(src/includes)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})
target_compile_options(pong PRIVATE -Wall -g)
target_link_libraries(pong ${SDL2_LIBRARIES})
target_link_libraries(pong ${SDL2_TTF_LIBRARIES})

add_custom_target(run_${EXEC} 
                  COMMAND ${EXEC}
                  DEPENDS ${EXEC}
                  COMMENT "Running ${EXEC}"
                  VERBATIM)
