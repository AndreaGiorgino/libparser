#include <iostream>

#include "libparser/parser.hxx"

static constexpr auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static constexpr libparser::parser::token tokenResult { 0, "#" };

auto TestParseFileStreamPeek(int, char**) -> int {
    libparser::parser p { testFilePath };

    {
        const auto token { p.peek() };
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
    {
        const auto token { p.peek() };
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
