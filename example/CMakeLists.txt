cmake_minimum_required(VERSION 3.24)

project(
    example
    LANGUAGES CXX
)

#
# Dependencies
#

include(FetchContent)

FetchContent_Declare(
    parser
    GIT_REPOSITORY git@github.com:AndreaGiorgino/libparser
    GIT_TAG 2.1.2
)

FetchContent_MakeAvailable(parser)

#
# Target
#

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(
    ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC parser
)
