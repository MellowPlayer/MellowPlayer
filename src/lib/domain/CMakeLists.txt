set(LIB_NAME "${PROJECT_NAME}.Domain")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS src/*.hpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_precompile_headers(${LIB_NAME} PUBLIC src/stdafx.h)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${LIB_NAME} Qt5::Core Qt5::Gui)