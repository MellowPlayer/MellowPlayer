include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/src/3rdparty/catch)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/src/3rdparty/fakeit)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/src/3rdparty/gtest-gmock)

add_definitions(-DPLUGINS_DIR=\"${CMAKE_SOURCE_DIR}/plugins\")
add_definitions(-DTEST_SUITE=1)
set(CMAKE_CXX_FLAGS ${TESTS_CMAKE_CXX_FLAGS})
set(CMAKE_AUTOMOC OFF)

add_subdirectory(lib)

add_unit_test(Domain)
add_unit_test(Infrastructure)
add_unit_test(Presentation)

add_integration_test(Infrastructure)
add_integration_test(Presentation)
if (UNIX AND NOT APPLE)
    add_integration_test(Mpris)
endif()

add_custom_target(AllTests COMMAND ctest --output-on-failure DEPENDS ${ALL_TESTS})
