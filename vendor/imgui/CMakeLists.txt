cmake_minimum_required(VERSION 3.25)

set(IMGUI_SRC 
		${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/imgui_demo.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_vulkan.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/imgui_stdlib.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp)

add_library(imgui STATIC ${IMGUI_SRC})

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)


