set(LIB_NAME "${PROJECT_NAME}.Infrastructure")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS src/*.hpp)

configure_file(${CMAKE_SOURCE_DIR}/scripts/settings/settings-schema.json ${CMAKE_CURRENT_BINARY_DIR}/resources/Settings/settings-schema.json )
configure_file(resources/infrastructure.qrc ${CMAKE_CURRENT_BINARY_DIR}/resources/infrastructure.qrc)
configure_file(resources/PluginTemplate/integration.js ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/integration.js)
configure_file(resources/PluginTemplate/metadata.ini ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/metadata.ini)
configure_file(resources/PluginTemplate/theme.json ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/theme.json)
configure_file(resources/PluginTemplate/logo.svg ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/logo.svg)
configure_file(resources/images/mellowplayer-connect.svg ${CMAKE_CURRENT_BINARY_DIR}/resources/images/mellowplayer-connect.svg)
configure_file(resources/scripts/install-mellowplayer-connect.sh ${CMAKE_CURRENT_BINARY_DIR}/resources/scripts/install-mellowplayer-connect.sh)
configure_file(resources/scripts/install-mellowplayer-connect.ps1 ${CMAKE_CURRENT_BINARY_DIR}/resources/scripts/install-mellowplayer-connect.ps1)

configure_file(src/MellowPlayer/Infrastructure/BuildConfig.cpp.in ${CMAKE_BINARY_DIR}/BuildConfig.cpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/resources/infrastructure.qrc ${CMAKE_BINARY_DIR}/BuildConfig.cpp)
target_precompile_headers(${LIB_NAME} REUSE_FROM ${PROJECT_NAME}.Domain)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${LIB_NAME} spdlog Qt5::Core Qt5::Gui Qt5::Concurrent Qt5::Network Qt5::Widgets Qt5::Sql ${PROJECT_NAME}.Domain)
