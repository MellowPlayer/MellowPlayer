find_package(qhotkey QUIET)
if (qhotkey_FOUND)
    message(STATUS "Found system qhotkey")
else()
    message(STATUS "Using FetchContent to retrieve QHotkey")
    FetchContent_Declare(
            qhotkey
            GIT_REPOSITORY https://github.com/Skycoder42/QHotkey.git
            GIT_TAG        1.4.1)
    option(QHOTKEY_INSTALL "Don't install QHotkey" OFF)
    FetchContent_MakeAvailable(qhotkey)
endif()
