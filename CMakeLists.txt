cmake_minimum_required(VERSION 3.11)

project(
    libparser
    VERSION 0.1.0
    LANGUAGES CXX
)

#
# Dependencies
#

include(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Options.cmake
)

#
# Target
#

file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx
)

add_library(
    ${PROJECT_NAME}
    STATIC ${SOURCE_FILES}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE -Wextra -Wall -pedantic
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/include
    COMMENT "Copying headers to build directory..."
)
