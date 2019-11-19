cmake_minimum_required(VERSION 3.0)

project(Obfuscate)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Functional test
add_executable(obfuscate_test obfuscate.h obfuscate_test.cpp)

# Bloat test
add_executable(obfuscate_test_bloat_on obfuscate.h obfuscate_test_bloat.cpp)
add_executable(obfuscate_test_bloat_off obfuscate.h obfuscate_test_bloat.cpp)
target_compile_definitions(obfuscate_test_bloat_on PRIVATE USE_AY_OBFUSCATE=1)