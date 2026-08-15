cmake_minimum_required(VERSION 3.23...4.0.0)

project(RayTracer LANGUAGES CXX)

add_executable(RayTracer 
src/raytrace.cpp)

target_compile_features(RayTracer PRIVATE cxx_std_23)
set_target_properties(RayTracer PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

target_include_directories(RayTracer PRIVATE
	include
)

if (MSVC)
	target_compile_options(RayTracer PRIVATE
	/W4
	/permissive-
	)
else() 
	target_compile_options(RayTracer PRIVATE
	-Wall
	-Wpedantic
	-Wreorder
	-Wnon-virtual-dtor
)
endif()
