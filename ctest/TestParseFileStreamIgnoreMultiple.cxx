#include <format>
#include <iostream>

#include "libparser/parser.hxx"

static const auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static const parser::token tokenResult { 9, "<" };

auto TestParseFileStreamIgnoreMultiple(int, char**) -> int {
    parser p { testFilePath };

    p.ignore(3);

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

    return 0;
}
