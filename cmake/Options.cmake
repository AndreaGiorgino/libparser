option(DEBUG "Enable the debug build." OFF)
option(PARSER_BUILD_TESTING "Enable testing and build the tests." OFF)
option(PARSER_BUILD_EXAMPLE "Build the example." OFF)

if(DEBUG)
    add_compile_definitions(DEBUG)
    add_compile_options(-g -ggdb -O0)
endif()

if(PARSER_BUILD_TESTING)
    enable_testing()
    add_subdirectory(ctest)
endif()
