find_path(BOOST_DI boost/di.hpp)
find_path(BOOST_DI_EXTENSION boost/di/extension/scopes/scoped.hpp)
if (BOOST_DI AND BOOST_DI_EXTENSION)
    set(SYSTEM_BOOST_DI_FOUND TRUE)
    set(BOOST_DI_EXTENSION_FOUND TRUE)
    set(BOOST_DI_INCLUDEDIR ${BOOST_DI})
    message(STATUS "Found system Boost.DI in ${BOOST_DI_INCLUDEDIR}")
else()
    set(SYSTEM_BOOST_DI_FOUND FALSE)
    message(STATUS "Using FetchContent to retrieve Boost.DI")
    FetchContent_Declare(
            Boost.DI
            GIT_REPOSITORY https://github.com/boost-ext/di.git
            GIT_TAG        v1.2.0)
    FetchContent_MakeAvailable(Boost.DI)
endif()
