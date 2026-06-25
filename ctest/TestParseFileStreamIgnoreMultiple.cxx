#include <iostream>

#include "libparser/parser.hxx"

static constexpr auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static constexpr libparser::parser::token tokenResult { 9, "<" };

auto TestParseFileStreamIgnoreMultiple(int, char**) -> int {
    libparser::parser p { testFilePath };

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
