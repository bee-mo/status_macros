cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

############################################################################## 
include(FetchContent)
FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
  OVERRIDE_FIND_PACKAGE
)
FetchContent_Declare(
 abseil
 GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
 GIT_TAG c2435f8342c2d0ed8101cb43adfd605fdc52dca2
 OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(gtest abseil)

############################################################################## 
project(absl_status_macros)

add_library(absl_ext_status_macros 
  status_macros.h
  status_builder.h
  status_builder.cc)

target_link_libraries(
  absl_ext_status_macros
  
  PRIVATE
  absl::core_headers
  absl::status
  absl::statusor
)
set_target_properties(absl_ext_status_macros PROPERTIES LINKER_LANGUAGE CXX)

############################################################################## 
enable_testing()
add_executable(
  status_macros_test
  status_macros_test.cc
)
target_link_libraries(
  status_macros_test

  PUBLIC
  absl_ext_status_macros
  GTest::gtest_main
  absl::status
  absl::statusor
  absl::strings
)

include(GoogleTest)
gtest_discover_tests(status_macros_test)

