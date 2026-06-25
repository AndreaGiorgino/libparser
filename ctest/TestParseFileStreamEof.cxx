#include <iostream>

#include "libparser/parser.hxx"

static constexpr auto testFilePath { "TestFiles/TestParseFileStream.txt" };

auto TestParseFileStreamEof(int, char**) -> int {
    libparser::parser p { testFilePath };

    {
        const auto isEof { p.eof() };
        if (isEof) {
            std::println(std::cerr,
                    "-- EOF not matching the expected result: "
                    "{} expected, got {} instead (streamoff: {}).",
                    false, isEof, p.tellg());
            return 1;
        }
    }

    while (!p.eof())
        p.ignore();

    {
        const auto isEof { p.eof() };
        if (!isEof) {
            std::println(std::cerr,
                    "-- EOF not matching the expected result: "
                    "{} expected, got {} instead (streamoff: {}).",
                    true, isEof, p.tellg());
            return 1;
        }
    }

    return 0;
}
