set(PROJECT_NAME Test)

cmake_minimum_required(VERSION 3.28)
project(${PROJECT_NAME})


set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES 
"${CMAKE_SOURCE_DIR}/src/*.cpp"
"${CMAKE_SOURCE_DIR}/src/*.ixx"
)


add_executable(${PROJECT_NAME}  ${SOURCES})

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Vulkan REQUIRED) 
find_package(glfw3 REQUIRED) 
find_package(Freetype REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Freetype::Freetype)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/glfw/include)
