cmake_minimum_required(VERSION 4.0)

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
#file(GLOB_RECURSE CPP_OTHER "${CMAKE_SOURCE_DIR}/vcpkg_installed/*.cppm")


find_package(Vulkan REQUIRED) 
find_package(glfw3 REQUIRED) 
find_package(Freetype REQUIRED)


add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${MODULE_SOURCES})


target_sources(${PROJECT_NAME}
    PRIVATE
    FILE_SET CXX_MODULES
    FILES
    ${MODULE_SOURCES}
    #${CPP_OTHER}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Freetype::Freetype)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
