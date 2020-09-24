macro(add_test_type layer type)
    file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${type}/${layer}/*.cpp)
    file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ${type}/${layer}/*.hpp)
    set(TEST_NAME ${PROJECT_NAME}.${layer}.${type})
    add_executable(${TEST_NAME} main.cpp ${SOURCE_FILES} ${HEADER_FILES})
    target_precompile_headers(${TEST_NAME} REUSE_FROM MellowPlayer.TestsLib)
    target_link_libraries(${TEST_NAME} MellowPlayer.Domain MellowPlayer.Presentation MellowPlayer.Infrastructure
            Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
            Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets Qt5::Test
            qxtglobalshortcut MellowPlayer.TestsLib)
    target_include_directories(${TEST_NAME} PRIVATE lib ${CMAKE_CURRENT_SOURCE_DIR} )
    target_include_directories(${TEST_NAME} SYSTEM PRIVATE
            ${CMAKE_SOURCE_DIR}/src/3rdparty
            ${CMAKE_SOURCE_DIR}/src/3rdparty/catch
            ${CMAKE_SOURCE_DIR}/src/3rdparty/fakeit)
    if (APPLE)
        add_framework(Carbon ${TEST_NAME})
        add_framework(Cocoa ${TEST_NAME})
    elseif(UNIX)
        find_package(X11)
        target_link_libraries(${TEST_NAME} ${X11_LIBRARIES} Qt5::DBus pthread)
    endif()

    if(USE_LIBNOTIFY)
        target_link_libraries(${TEST_NAME} ${LIBNOTIFY_LIBRARIES})
    endif()

    add_test (NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}> -s)
    set(ALL_TESTS ${ALL_TESTS} ${TEST_NAME})
endmacro()

macro(add_unit_test layer)
    add_test_type(${layer} UnitTests)
endmacro()

macro(add_integration_test layer)
    add_test_type(${layer} IntegrationTests)
endmacro()