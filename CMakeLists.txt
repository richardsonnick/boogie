cmake_minimum_required(VERSION 3.14)

project(boogie VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")


set(CTEST_OUTPUT_ON_FAILURE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(boogie
  src/main.cpp
)

target_include_directories(boogie PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(boogie PRIVATE -Wall -Wextra -Wpedantic)

add_library(boogie_lib
  src/hash/sha1.cpp
  src/util/utils.cpp
)

target_include_directories(boogie_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/util
)

target_compile_options(boogie_lib PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(boogie PRIVATE boogie_lib)

install(TARGETS boogie_lib
  EXPORT boogie_lib_export
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install the public headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include
)

# Export the library for use by other projects
install(EXPORT boogie_lib_export
  FILE boogie_lib-config.cmake
  DESTINATION lib/cmake/boogie_lib
)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(GTEST_CREATE_SHARED_LIBRARY OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(boogie_tests
  test/sha1_test.cpp
)

target_include_directories(boogie_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(boogie_tests
  PRIVATE
  gtest
  gtest_main
  pthread
  boogie_lib
)

include(GoogleTest)
gtest_discover_tests(boogie_tests)

install(TARGETS boogie DESTINATION bin)