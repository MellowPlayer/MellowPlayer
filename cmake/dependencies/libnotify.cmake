if(UNIX AND NOT APPLE)
    find_package(PkgConfig)
    pkg_search_module(LIBNOTIFY REQUIRED libnotify)
    if (LIBNOTIFY_FOUND)
        message(STATUS "Found libnotify ${LIBNOTIFY_VERSION} in ${LIBNOTIFY_LIBDIR}")
        set(USE_LIBNOTIFY ON)
    else ()
        message(STATUS "libnotify not found, system tray icon based notifications will be enabled")
    endif()
endif()