cmake_minimum_required(VERSION 2.8)

add_subdirectory(repo)

project(spirv)

message(STATUS "Trying to add the addon ${CMAKE_CURRENT_LIST_DIR}")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/repo/)
include_directories(${OPIFEX_ENGINE_REPOSITORY})

add_external_opifex_includes()

add_library(spirv
	"source/OPspirv.cpp")
	
add_opifex_defines()
target_link_libraries(spirv spirv-cross-core spirv-cross-glsl)



set_property(TARGET imgui PROPERTY FOLDER "Addons")

