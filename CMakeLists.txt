cmake_minimum_required(VERSION 3.15...4.0)

project(boogie VERSION 1.0
  DESCRIPTION "A crypto library"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Set the output directory to be in build/bin
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
set(CTEST_OUTPUT_ON_FAILURE ON)
set(CMAKE_INSTALL_RPATH "/usr/local/lib") # TODO is this only needed on macos??

## LIBRARY SETUP
add_library(boogielib SHARED src/hash/sha1.cpp src/util/utils.cpp
  include/hash/sha1.h src/util/utils.h)
target_include_directories(boogielib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE src/util)
target_compile_options(boogielib PRIVATE -Wall -Wextra -Wpedantic)
install(TARGETS boogielib
  EXPORT boogielib_export
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include
)
install(EXPORT boogielib_export
  FILE boogielib-config.cmake
  DESTINATION lib/cmake/boogielib
)

## EXECUTABLE SETUP
add_executable(boogie src/main.cpp)
target_link_libraries(boogie PRIVATE boogielib)
target_compile_options(boogie PRIVATE -Wall -Wextra -Wpedantic)
install(TARGETS boogie DESTINATION bin)

## TESTING SETUP
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
  boogielib
)

include(GoogleTest)
gtest_discover_tests(boogie_tests)
