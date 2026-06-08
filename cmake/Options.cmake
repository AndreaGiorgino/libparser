option(DEBUG "Enable debug build." OFF)
option(PARSER_BUILD_TESTING "Enable testing and build tests." OFF)

if(DEBUG)
    add_compile_definitions(DEBUG)
    add_compile_options(-g -ggdb)
endif()

if(PARSER_BUILD_TESTING)
    enable_testing()
    add_subdirectory(ctest)
endif()
