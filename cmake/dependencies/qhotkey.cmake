find_package(QHotkey QUIET)
if (QHotkey_FOUND)
    message(STATUS "Found system QHotkey")
else()
    message(STATUS "Using FetchContent to retrieve QHotkey")
    FetchContent_Declare(
            qhotkey
            GIT_REPOSITORY https://github.com/Skycoder42/QHotkey.git
            GIT_TAG        bd35d8b07a0bff99238d72055fc43a2be4df38aa
    )
    option(QHOTKEY_INSTALL "Don't install QHotkey" OFF)
    FetchContent_MakeAvailable(qhotkey)
endif()
