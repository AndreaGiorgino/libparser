#include <array>
#include <iostream>

#include "libparser/parser.hxx"

static constexpr auto testFilePath { "TestFiles/TestParseFileStream.txt" };
static constexpr std::array<libparser::parser::token, 2> tokensResult {{
    { 0, "#" }, { 1, "include" },
}};

auto TestParseFileStreamGet(int, char**) -> int {
    libparser::parser p { testFilePath };

    const auto lambda {
        [&](size_t resultindex) -> int {
            const auto token { p.get() };
            if (const auto& tokenResult { tokensResult[resultindex] };
                    token.position != tokenResult.position
                    || token.literal != tokenResult.literal) {
                std::println(std::cerr,
                        "-- Token not matching the expected result: "
                        "\"{{ {}, {:?} }}\" expected, got "
                        "\"{{ {}, {:?} }}\" instead.",
                        tokenResult.position, tokenResult.literal,
                        token.position, token.literal);
                return 1;
            }
            return 0;
        }
    };

    for (size_t i {}; i < tokensResult.size(); i++)
        if (const auto ret { lambda(i) };
                ret != 0)
            return ret;

    return 0;
}
