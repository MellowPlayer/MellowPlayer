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
if (ENABLE_QUICK_COMPILER)
    find_package(Qt5QuickCompiler REQUIRED)
endif()
if (ENABLE_QML_LINT)
    find_package(QmlLint)
endif()

if (UNIX AND NOT APPLE)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS DBus X11Extras)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
message(STATUS "Found Qt ${Qt5_VERSION} in ${Qt5_DIR}")