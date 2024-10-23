cmake_minimum_required (VERSION 3.14)
project (cmocka_template)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories for source code
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

# cmocka
option(ENABLE_TESTS "Perform unit tests after build" OFF)
if (ENABLE_TESTS)
  enable_testing()

  include(FetchCMocka)
  include(AddCMockaTest)
  include(AddMockedTest)
  add_subdirectory(test)
endif(ENABLE_TESTS)
