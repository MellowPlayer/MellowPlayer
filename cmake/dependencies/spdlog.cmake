find_package(spdlog QUIET)
if (spdlog_FOUND)
    message(STATUS "Found system spdlog")
else()
    message(STATUS "Using FetchContent to retrieve spdlog")
    FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG        v1.8.0)
    FetchContent_MakeAvailable(spdlog)
endif()