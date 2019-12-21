set(LIB_NAME "${PROJECT_NAME}.Application")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.hpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${LIB_NAME} PUBLIC Qt5::Core Qt5::Gui ${PROJECT_NAME}.Domain ${PROJECT_NAME}.Infrastructure ${PROJECT_NAME}.Presentation)