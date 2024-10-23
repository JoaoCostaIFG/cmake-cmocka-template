add_mocked_test(add SOURCES ${CMAKE_SOURCE_DIR}/src/add.c)
add_mocked_test(add3 SOURCES ${CMAKE_SOURCE_DIR}/src/add3.c MOCKS add)
add_mocked_test(add_internal)
