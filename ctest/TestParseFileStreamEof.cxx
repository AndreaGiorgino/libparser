#include <iostream>

#include "libparser/parser.hxx"

static constexpr auto testFilePath { "TestFiles/TestParseFileStream.txt" };

auto TestParseFileStreamEof(int, char**) -> int {
    libparser::parser p { testFilePath };

    const auto lambda {
        [&](bool expected) -> int {
            if (p.eof() != expected) {
                std::println(std::cerr,
                        "-- EOF not matching the expected result: "
                        "{} expected, got {} instead (streamoff: {}).",
                        expected, p.eof(), p.tellg());
                return 1;
            }
            return 0;
        }
    };

    if (const auto ret { lambda(false) };
            ret != 0)
        return ret;

    // skip all tokens
    for (const auto& _ : p.tokens()) {}

    if (const auto ret { lambda(true) };
            ret != 0)
        return ret;

    return 0;
}
