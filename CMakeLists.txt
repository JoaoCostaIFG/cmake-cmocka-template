cmake_minimum_required (VERSION 3.14)
project (cmocka_template)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Werror")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
include(static-analysis)

# Coverage needs some compile flags
if (ENABLE_COVERAGE)
  set(COVERAGE_FLAGS -g -O0 --coverage)
  add_compile_options(${COVERAGE_FLAGS})
  link_libraries(${COVERAGE_FLAGS})
endif (ENABLE_COVERAGE)

# Include directories for source code
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# Source code dir has its own CMakeLists
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${SRC_DIR})

# Unit tests
option(ENABLE_TESTS "Perform unit tests after build" OFF)
if (ENABLE_TESTS)
  enable_testing()

  include(FetchCMocka)
  include(AddCMockaTest)
  include(AddMockedTest)
  add_subdirectory(test)

  if (ENABLE_COVERAGE)
    add_custom_target(coverage
      # COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/src --html --html-details -o coverage.html
      # COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/src -s
      COMMAND gcovr -r ${CMAKE_CURRENT_SOURCE_DIR} --filter ${SRC_DIR} --html --html-details --merge-mode-functions=separate -o coverage.html
      COMMAND gcovr -r ${CMAKE_CURRENT_SOURCE_DIR} --filter ${SRC_DIR} -s --merge-mode-functions=separate
    )
  endif (ENABLE_COVERAGE)
endif(ENABLE_TESTS)
