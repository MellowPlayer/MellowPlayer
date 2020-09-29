set(LIB_NAME "${PROJECT_NAME}.Domain")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS src/*.hpp)

if (MSVC_COMPILER)
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
else()
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
    set_target_properties(${LIB_NAME} PROPERTIES DEFINE_SYMBOL "" )
    install(TARGETS ${LIB_NAME}
            BUNDLE DESTINATION MacOS
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/static)
endif()
target_precompile_headers(${LIB_NAME} PUBLIC src/stdafx.h)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${LIB_NAME} Qt5::Core Qt5::Gui)
