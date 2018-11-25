set(LIB_NAME "${PROJECT_NAME}.Infrastructure")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

configure_file(${CMAKE_SOURCE_DIR}/scripts/settings/schema.json.in ${CMAKE_CURRENT_BINARY_DIR}/resources/Settings/schema.json )
configure_file(resources/infrastructure.qrc ${CMAKE_CURRENT_BINARY_DIR}/resources/infrastructure.qrc)
configure_file(resources/PluginTemplate/integration.js ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/integration.js)
configure_file(resources/PluginTemplate/metadata.ini ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/metadata.ini)
configure_file(resources/PluginTemplate/theme.json ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/theme.json)
configure_file(resources/PluginTemplate/logo.svg ${CMAKE_CURRENT_BINARY_DIR}/resources/PluginTemplate/logo.svg)

configure_file(src/BuildConfig.cpp.in ${CMAKE_BINARY_DIR}/BuildConfig.cpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/resources/infrastructure.qrc ${CMAKE_BINARY_DIR}/BuildConfig.cpp)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/3rdparty/spdlog-0.16.3/include)
target_link_libraries(${LIB_NAME} Qt5::Core Qt5::Gui Qt5::Concurrent Qt5::Widgets ${PROJECT_NAME}.Domain)