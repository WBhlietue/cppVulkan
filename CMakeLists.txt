set(PROJECT_NAME Test)

cmake_minimum_required(VERSION 3.15)
project(${PROJECT_NAME})


set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_subdirectory(thirdparty/glfw)

file(GLOB_RECURSE  SOURCES 
"${CMAKE_SOURCE_DIR}/src/*.cpp"
# "${CMAKE_SOURCE_DIR}/main/windows/*.cpp"
)

add_executable(${PROJECT_NAME}  ${SOURCES})

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Vulkan REQUIRED) 
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/glfw/include)
