set(QT_MIN_VERSION 5.15)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Concurrent
        Core
        Gui
        Network
        Qml
        Quick
        QuickControls2
        Sql
        Svg
        Test
        WebEngine
        WebChannel
        WebEngineWidgets
        Widgets)

find_package(Qt5LinguistTools REQUIRED)

if (UNIX AND NOT APPLE)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS DBus)
    include_directories(${QtDBus_INCLUDE_DIRS})
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
message(STATUS "Found Qt ${Qt5_VERSION} in ${Qt5_DIR}")

if(UNIX AND NOT APPLE)
    find_package(PkgConfig)
    pkg_search_module(LIBNOTIFY REQUIRED libnotify)
    if (LIBNOTIFY_FOUND)
        message(STATUS "Found libnotify ${LIBNOTIFY_VERSION} in ${LIBNOTIFY_LIBDIR}")
        link_directories(${LIBNOTIFY_LIBDIR})
        add_definitions(-DUSE_LIBNOTIFY)
        set(USE_LIBNOTIFY ON)
    else ()
        message(STATUS "libnotify not found, system tray icon based notifications will be enabled")
    endif()
endif()

find_package(qxtglobalshortcut QUIET)
if (qxtglobalshortcut_FOUND)
    message(STATUS "Found qxtglobalshortcut")
else()
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/3rdparty/libqxt)
endif()