#include <format>
#include <iostream>

#include "libparser/parser.hxx"

static const auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static const parser::token tokenResult { 0, "#" };

auto TestParseFileStreamSeek(int, char**) -> int {
    parser p { testFilePath };

    {
        const auto token { p.get() };
        if (token.position != tokenResult.position
                || token.literal != tokenResult.literal) {
            std::println(std::cerr,
                    "-- Token not matching the expected result: "
                    "\"{{ {}, {:?} }}\" expected, got \"{{ {}, {:?} }}\" instead.",
                    tokenResult.position, tokenResult.literal,
                    token.position, token.literal);
            return 1;
        }
    }

    p.seekg(0);

    {
        const auto token { p.get() };
        if (token.position != tokenResult.position
                || token.literal != tokenResult.literal) {
            std::println(std::cerr,
                    "-- Token not matching the expected result: "
                    "\"{{ {}, {:?} }}\" expected, got \"{{ {}, {:?} }}\" instead.",
                    tokenResult.position, tokenResult.literal,
                    token.position, token.literal);
            return 1;
        }
    }

    return 0;
}
