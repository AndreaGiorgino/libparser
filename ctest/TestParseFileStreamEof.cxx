#include <format>
#include <iostream>

#include "libparser/parser.hxx"

static const auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static const parser::token tokenResult { 111, std::string { (char)EOF } };

auto TestParseFileStreamEof(int, char**) -> int {
    parser p { testFilePath };

    {
        const auto isEof { p.eof() };
        if (isEof) {
            std::println(std::cerr,
                    "-- EOF not matching the expected result: "
                    "{} expected, got {} instead.",
                    false, isEof);
            return 1;
        }
    }

    for ([[maybe_unused]] const auto& token : p.tokens()) {}

    {
        const auto isEof { p.eof() };
        if (!isEof) {
            std::println(std::cerr,
                    "-- EOF not matching the expected result: "
                    "{} expected, got {} instead.",
                    true, isEof);
            return 1;
        }
    }

    return 0;
}
