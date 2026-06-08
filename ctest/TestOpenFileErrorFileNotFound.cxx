#include <iostream>

#include "libparser/libparser.hxx"
#include "libparser/errors/file_error.hxx"

static const auto testFilePath { "TestFiles/TestFileNotFound.txt" };

auto TestOpenFileErrorFileNotFound(int, char**) -> int {
    try {
        parser p { testFilePath };
    } catch (const errors::file_error& err) {
        return 0;
    } catch (const std::exception& err){
        std::cerr << err.what() << std::endl;
        return 1;
    }

    return 0;
}
