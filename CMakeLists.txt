cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(PROJECT_NAME Test)

project(${PROJECT_NAME})


set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_compile_options(/experimental:module)
endif()


file(GLOB_RECURSE MODULE_SOURCES "${CMAKE_SOURCE_DIR}/src/*.ixx")
file(GLOB_RECURSE CPP_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")



find_package(Vulkan REQUIRED) 
find_package(glfw3 REQUIRED) 
find_package(Freetype REQUIRED)

#add_library(${PROJECT_NAME} STATIC   ${CPP_SOURCES}   ${MODULE_SOURCES})

add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${MODULE_SOURCES})


target_sources(${PROJECT_NAME}
    PRIVATE
    FILE_SET CXX_MODULES
    FILES
    ${MODULE_SOURCES}
    #${CPP_OTHER}
)
target_precompile_headers(${PROJECT_NAME} PRIVATE
    <vector>
    <string>
    <iostream>
    <vulkan/vulkan.hpp>
    <glm/glm.hpp>
    <GLFW/glfw3.h>
    <iostream>
    <fstream>
    <stdexcept>
    <algorithm>
    <vector>
    <cstring>
    <cstdlib>
    <cstdint>
    <limits>
    <array>
    <optional>
    <set>
    <chrono>
    <thread>
)


target_link_libraries(${PROJECT_NAME} PUBLIC Freetype::Freetype)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
