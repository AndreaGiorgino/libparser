#include <iostream>

#include "libparser/parser.hxx"

static constexpr auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static constexpr auto positionResult { 2 };

auto TestParseFileStreamTell(int, char**) -> int {
    libparser::parser p { testFilePath };

    p.ignore();

    const auto position { p.tellg() };
    const auto token { p.get() };
    if (token.position != position) {
        std::println(std::cerr,
                "-- Position not matching the expected result: "
                "{} expected, got {} instead.",
                positionResult, position);
        return 1;
    }

    return 0;
}
