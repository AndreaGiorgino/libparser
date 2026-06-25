#include <array>
#include <iostream>

#include "libparser/parser.hxx"

static constexpr auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static constexpr std::array<libparser::parser::token, 2> tokensResult {{
    { 0, "#" }, { 1, "include" },
}};

auto TestParseFileStreamGet(int, char**) -> int {
    libparser::parser p { testFilePath };

    size_t i {};
    {
        const auto token { p.get() };
        if (const auto& tokenResult { tokensResult[i++] };
                token.position != tokenResult.position
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
        const auto token { p.get() };
        if (const auto& tokenResult { tokensResult[i++] };
                token.position != tokenResult.position
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
