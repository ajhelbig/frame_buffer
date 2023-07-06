cmake_minimum_required(VERSION 3.22.1)

project(ProjectName
	LANGUAGES CXX C
)

include_directories(include)

set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)
add_subdirectory(src)