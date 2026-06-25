#include <iostream>

#include "libparser/parser.hxx"
#include "libparser/errors/file_error.hxx"

static constexpr auto testFilePath { "TestFiles/TestOpenFile.txt" };

auto TestOpenFile(int, char**) -> int {
    try {
        libparser::parser p { testFilePath };
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    return 0;
}
