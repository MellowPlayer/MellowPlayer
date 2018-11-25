#
# Tests
#

enable_testing()

find_package(Threads)

# Build Catch unit tests
add_library(catch INTERFACE)
target_include_directories(catch INTERFACE .)

file(GLOB catch_tests LIST_DIRECTORIES false RELATIVE . *.cpp *.h *.hpp)

add_executable(catch_tests ${catch_tests})
target_link_libraries(catch_tests spdlog ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME catch_tests COMMAND catch_tests)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")

