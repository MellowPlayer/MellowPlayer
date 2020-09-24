# Translation files
file(GLOB_RECURSE TS_FILES CONFIGURE_DEPENDS languages/*.ts)
qt5_add_translation(QM_FILES ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES} ${TS_FILES})

# generate languages.qrc
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/languages.qrc "<!DOCTYPE RCC>\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/languages.qrc "<RCC version=\"1.0\">\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/languages.qrc "    <qresource prefix=\"/MellowPlayer/Translations\">\n")
foreach(FILE ${QM_FILES})
    string(REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" RELATIVE_PATH ${FILE})
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/languages.qrc "        <file>${RELATIVE_PATH}</file>\n")
endforeach()
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/languages.qrc "    </qresource>\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/languages.qrc "</RCC>\n")
set_property(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/qrc_languages.cpp PROPERTY SKIP_AUTOMOC ON)

# Create main executable
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lib/*.hpp)
set(SOURCE_FILES main.cpp)
if(WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} MellowPlayer.rc)
    configure_file(../../scripts/ci/windows/setup_templ.iss ${CMAKE_BINARY_DIR}/setup.iss)
endif()
add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32 ${SOURCE_FILES} ${QM_FILES} ${CMAKE_CURRENT_BINARY_DIR}/languages.qrc qml.qrc)
add_dependencies(${PROJECT_NAME} translations)
target_precompile_headers(${PROJECT_NAME} REUSE_FROM ${PROJECT_NAME}.Domain)
target_link_libraries(${PROJECT_NAME}
        MellowPlayer.Domain
        MellowPlayer.Presentation
        MellowPlayer.Infrastructure
        MellowPlayer.Application
        Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
        Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets Qt5::WebChannel qxtglobalshortcut)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_QXT_CORE -DBUILD_QXT_GUI -DQXT_STATIC)

if (APPLE)
    add_framework(Carbon ${PROJECT_NAME})
    add_framework(Cocoa ${PROJECT_NAME})
elseif(UNIX)
    find_package(X11)
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} Qt5::DBus)
    if (STATIC_LIBSTDCPP)
        message(STATUS "Linking statically to libgcc and libstdc++")
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    endif()
    if(USE_LIBNOTIFY)
        target_link_libraries(${PROJECT_NAME} ${LIBNOTIFY_LIBRARIES})
        target_link_directories(${PROJECT_NAME} PRIVATE ${LIBNOTIFY_LIBDIR})
        target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_LIBNOTIFY)
    endif()
endif()

# add a console based executable for easier debugging
if (WIN32)
    add_executable(MellowPlayer.Console MACOSX_BUNDLE ${SOURCE_FILES})
    target_precompile_headers(MellowPlayer.Console REUSE_FROM ${PROJECT_NAME}.Domain)
    target_link_libraries(MellowPlayer.Console
            MellowPlayer.Domain
            MellowPlayer.Presentation
            MellowPlayer.Infrastructure
            MellowPlayer.Application
            Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
            Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets qxtglobalshortcut)
    target_compile_definitions(MellowPlayer.Console PRIVATE -DBUILD_QXT_CORE -DBUILD_QXT_GUI -DQXT_STATIC)
endif()

install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION MacOS
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/static)
install(DIRECTORY share/applications DESTINATION ${CMAKE_INSTALL_DATADIR})
install(DIRECTORY share/icons DESTINATION ${CMAKE_INSTALL_DATADIR})

string(TIMESTAMP _date "%Y-%m-%d")
configure_file(share/metainfo/com.gitlab.ColinDuquesnoy.MellowPlayer.metainfo.xml ${CMAKE_BINARY_DIR}/com.gitlab.ColinDuquesnoy.MellowPlayer.metainfo.xml)
install(FILES ${CMAKE_BINARY_DIR}/com.gitlab.ColinDuquesnoy.MellowPlayer.metainfo.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)