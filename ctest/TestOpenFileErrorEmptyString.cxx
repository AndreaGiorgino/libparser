#include <iostream>

#include "libparser/parser.hxx"
#include "libparser/errors/file_error.hxx"

static constexpr auto testFilePath { "" };

auto TestOpenFileErrorEmptyString(int, char**) -> int {
    try {
        libparser::parser p { testFilePath };
    } catch (const libparser::errors::file_error& err) {
        return 0;
    } catch (const std::exception& err){
        std::cerr << err.what() << std::endl;
        return 1;
    }

    return 0;
}
