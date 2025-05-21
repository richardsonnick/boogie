cmake_minimum_required(VERSION 3.10)

project(boogie VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

set(CTEST_OUTPUT_ON_FAILURE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(boogie
  src/main.cpp
)

target_include_directories(boogie PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


target_compile_options(boogie PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
find_package(GTest REQUIRED)
add_executable(boogie_tests
  test/utils_test.cpp
)
target_include_directories(boogie_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(boogie_tests
  PRIVATE
  GTest::gtest
  GTest::gtest_main
  pthread
)

include(GoogleTest)
gtest_discover_tests(boogie_tests)

install(TARGETS boogie DESTINATION bin)