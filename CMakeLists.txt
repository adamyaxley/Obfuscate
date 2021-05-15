cmake_minimum_required(VERSION 3.14)

project(Obfuscate)

option(GENERATE_TESTS "GENERATE_TESTS" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

    add_executable(obfuscate_test obfuscate.h obfuscate_test.cpp)
    target_link_libraries(obfuscate_test gtest_main)

    add_test(NAME obfuscate_test COMMAND obfuscate_test)
endif()

# Bloat test
add_executable(obfuscate_test_bloat_on obfuscate.h obfuscate_test_bloat.cpp)
add_executable(obfuscate_test_bloat_off obfuscate.h obfuscate_test_bloat.cpp)
target_compile_definitions(obfuscate_test_bloat_on PRIVATE USE_AY_OBFUSCATE=1)