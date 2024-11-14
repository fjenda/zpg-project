cmake_minimum_required(VERSION 3.26)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64)
endif()

project(zpgProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -pedantic -flto -march=native -mtune=native")

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_compile_definitions(ZPG_SAFE_PIXEL_ACCESS)
add_compile_definitions(ZPG_PERF)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(ZPG_DEBUG)
    message("BUILDING WITH DEBUG MODE")
endif()

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")

file(GLOB SOURCES "src/*.cpp" "Scenes/*.cpp")
file(GLOB HEADERS "Include/*.h" "Scenes/*.h")
file(GLOB MODELS "models/*.h")
file(GLOB LIB_H "lib/*.h")
file(GLOB_RECURSE LIB_CPP "lib/*.cpp")

add_executable(ZPG main.cpp ${SOURCES} ${HEADERS} ${MODELS} ${LIB_H} ${LIB_CPP} )

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

target_link_libraries(ZPG GLEW::glew)
target_link_libraries(ZPG glfw)
target_link_libraries(ZPG OpenGL::GL)
target_link_libraries(ZPG glm::glm)
target_link_libraries(ZPG assimp::assimp)
target_include_directories(ZPG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)