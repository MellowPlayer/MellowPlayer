Include(FetchContent)

set( CMAKE_PROJECT_INCLUDE_BEFORE ${CMAKE_SOURCE_DIR}/cmake/LoadAlwaysBeforeProject.cmake )

include(cmake/dependencies/qt.cmake)
include(cmake/dependencies/qt.cmake)
include(cmake/dependencies/libnotify.cmake)
include(cmake/dependencies/qxt.cmake)
include(cmake/dependencies/catch.cmake)
include(cmake/dependencies/boost-di.cmake)

