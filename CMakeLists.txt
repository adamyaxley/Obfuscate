cmake_minimum_required(VERSION 3.8)
project(Obfuscate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(include/${PROJECT_NAME})

#if (CATKIN_ENABLE_TESTING)
#	add_subdirectory(test)
#endif()

install(
	DIRECTORY "include/${PROJECT_NAME}/"
	DESTINATION "/usr/include"
)
