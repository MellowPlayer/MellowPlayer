set(LIB_NAME "${PROJECT_NAME}.Presentation")

set(EXCLUDE_DIRS "Linux")
glob_recurse_excl(HEADER_FILES src/*.hpp "${EXCLUDE_DIRS}")
glob_recurse_excl(SOURCE_FILES src/*.cpp "${EXCLUDE_DIRS}")

file(GLOB_RECURSE QML_FILES CONFIGURE_DEPENDS imports/*.qml)
file(GLOB_RECURSE QRC_FILES CONFIGURE_DEPENDS *.qrc)
file(GLOB_RECURSE CONF_FILES CONFIGURE_DEPENDS *.conf)

set(QML_FILES ${QML_FILES} imports/MellowPlayer/qmldir)
if(UNIX AND NOT APPLE)
    glob_recurse_excl(MPRIS_HEADER_FILES src/MellowPlayer/Presentation/Mpris/Linux/*.hpp "")
    glob_recurse_excl(MPRIS_SOURCE_FILES src/MellowPlayer/Presentation/Mpris/Linux/*.cpp "")
    set(SOURCE_FILES ${SOURCE_FILES} ${MPRIS_SOURCE_FILES})
    set(HEADER_FILES ${HEADER_FILES} ${MPRIS_HEADER_FILES})
    if(USE_LIBNOTIFY)
        glob_recurse_excl(LIBNOTIFY_PRESENTER_HEADER_FILES src/MellowPlayer/Presentation/Notifications/Presenters/Linux/*.hpp "")
        glob_recurse_excl(LIBNOTIFY_PRESENTER_SOURCE_FILES src/MellowPlayer/Presentation/Notifications/Presenters/Linux/*.cpp "")
        set(SOURCE_FILES ${SOURCE_FILES} ${LIBNOTIFY_PRESENTER_SOURCE_FILES})
        set(HEADER_FILES ${HEADER_FILES} ${LIBNOTIFY_PRESENTER_HEADER_FILES})
    endif()
endif()

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES} ${CONF_FILES})
target_precompile_headers(${LIB_NAME} REUSE_FROM ${PROJECT_NAME}.Domain)
target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.Domain ${PROJECT_NAME}.Infrastructure
                      Qt5::Core Qt5::Qml Qt5::Quick Qt5::QuickControls2 Qt5::Svg
                      Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets qxtglobalshortcut)
target_include_directories(${LIB_NAME} PUBLIC src)
if(USE_LIBNOTIFY)
    target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${LIBNOTIFY_INCLUDE_DIRS})
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(${LIB_NAME} Qt5::DBus)
    if(USE_LIBNOTIFY)
        target_link_libraries(${LIB_NAME} ${LIBNOTIFY_LIBRARIES})
    endif()
endif()

