#include <iostream>

#include "libparser/parser.hxx"
#include "libparser/errors/file_error.hxx"

static const auto testFilePath { "" };

auto TestOpenFileErrorEmptyString(int, char**) -> int {
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
