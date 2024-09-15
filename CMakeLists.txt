cmake_minimum_required(VERSION 3.25)

project(vkglfw)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)

add_executable(vkglfw src/main.cpp src/mvk.cpp)
target_include_directories(vkglfw PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(vendor/glfw-3.4 EXCLUDE_FROM_ALL)
add_subdirectory(vendor/imgui EXCLUDE_FROM_ALL)
add_subdirectory(vendor/box2d EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glm-1.0.1 EXCLUDE_FROM_ALL)


target_link_libraries(vkglfw PRIVATE glfw Vulkan::Vulkan imgui  box2d glm::glm )

