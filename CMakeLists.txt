cmake_minimum_required(VERSION 3.26)
set(CMAKE_OSX_ARCHITECTURES x86_64)
project(zpgProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -pedantic -flto -march=native -mtune=native")

add_compile_definitions(ZPG_SAFE_PIXEL_ACCESS)
add_compile_definitions(ZPG_PERF)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(ZPG_DEBUG)
    message("BUILDING WITH DEBUG MODE")
endif()

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")


add_executable(ZPG
        main.cpp
        Application/Application.cpp
        Application/Application.h
        Enums/Colors.h
        Enums/ModelKind.h
        Models/Models.h
        Models/plain.h
        Models/pyramid.h
        Models/sphere.h
        Models/square.h
        Models/suzi_flat.h
        Models/suzi_smooth.h
        Models/triangle.h
        RenderableModel/RenderableModel.cpp
        RenderableModel/RenderableModel.h
        RenderableModel/Model/Model.cpp
        RenderableModel/Model/Model.h
        RenderableModel/Shader/Shader.cpp
        RenderableModel/Shader/Shader.h
        RenderableModel/Transformation/Transformation.cpp
        RenderableModel/Transformation/Transformation.h
        Scene/Scene.cpp
        Scene/Scene.h
        ModelLoader/ModelLoader.cpp
        ModelLoader/ModelLoader.h
        RenderableModel/Transformation/Rotation.cpp
        RenderableModel/Transformation/Rotation.h
        RenderableModel/Transformation/Scale.cpp
        RenderableModel/Transformation/Scale.h
        RenderableModel/Transformation/Translation.cpp
        RenderableModel/Transformation/Translation.h
        RenderableModel/Transformation/Composite.cpp
        RenderableModel/Transformation/Composite.h
        Camera/Camera.cpp
        Camera/Camera.h
        CallbackController/CallbackController.cpp
        CallbackController/CallbackController.h
        RenderableModel/Shader/Observer.cpp
        RenderableModel/Shader/Observer.h
)

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
