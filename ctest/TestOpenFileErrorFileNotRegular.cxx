#include <iostream>

#include "libparser.hxx"
#include "errors/file_error.hxx"

static const auto testFilePath { "TestFiles" };

auto TestOpenFileErrorFileNotRegular(int, char**) -> int {
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
