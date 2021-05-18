cmake_minimum_required(VERSION 3.14)

project(Obfuscate)

option(GENERATE_TESTS "GENERATE_TESTS" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set unix platforms to output executables to Release and Debug folders (Windows does by default)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)

# Unit tests
if (GENERATE_TESTS)
    include(CTest)

    include(FetchContent)
    FetchContent_Declare(
      googletest
      # Specify the commit you depend on and update it regularly.
      URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(test_unit obfuscate.h test_unit.cpp)
    target_link_libraries(test_unit gtest_main)

    add_test(NAME test_unit COMMAND test_unit)

    add_executable(test_obfuscated obfuscate.h test_obfuscated.cpp)
    set_target_properties(test_obfuscated PROPERTIES SUFFIX ".out")
endif()

# Bloat test
add_executable(test_bloat_on obfuscate.h test_bloat.cpp)
add_executable(test_bloat_off obfuscate.h test_bloat.cpp)
target_compile_definitions(test_bloat_on PRIVATE USE_AY_OBFUSCATE=1)