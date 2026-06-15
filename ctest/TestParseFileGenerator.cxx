#include <array>
#include <format>
#include <iostream>

#include "libparser/parser.hxx"

static const auto testFilePath { "TestFiles/TestParseFileGenerator.txt" };
static const std::array<parser::token, 56> tokensResult {{
    { 0,   "#"      }, { 1,   "include" }, { 8,   " "     }, { 9,  "<"       },
    { 10,  "print"  }, { 15,  ">"       }, { 16,  "\n"    }, { 17,  "\n"      },
    { 18,  "auto"   }, { 22,  " "       }, { 23,  "main"  }, { 27,  "("       },
    { 28,  "int"    }, { 31,  " "       }, { 32,  "argc"  }, { 36,  ","       },
    { 37,  " "      }, { 38,  "char"    }, { 42,  "*"     }, { 43,  "*"       },
    { 44,  " "      }, { 45,  "argv"    }, { 49,  ")"     }, { 50,  " "       },
    { 51,  "-"      }, { 52,  ">"       }, { 53,  " "     }, { 54,  "int"     },
    { 57,  " "      }, { 58,  "{"       }, { 59,  "\n"    }, { 60,  "    "    },
    { 64,  "std"    }, { 67,  ":"       }, { 68,  ":"     }, { 69,  "println" },
    { 76,  "("      }, { 77,  "\""      }, { 78,  "Hello" }, { 83,  ","       },
    { 84,  " "      }, { 85,  "world"   }, { 90,  "!"     }, { 91,  "\""      },
    { 92,  ")"      }, { 93,  ";"       }, { 94,  "\n"    }, { 95,  "    "    },
    { 99, "return" }, { 105, " "       }, { 106, "0"     }, { 107, ";"       },
    { 108, "\n"     }, { 109, "}"       }, { 110, "\n"    },
    { 111, std::string { (char)EOF } },
}};

auto TestParseFileGenerator(int, char**) -> int {
    parser p { testFilePath };

    size_t i {};
    for (const auto& token : p.tokens()) {
        if (i >= tokensResult.size()) {
            std::println(std::cerr,
                    "-- Token index out of bounds: accessing index {} "
                    "out of {} expected tokens.",
                    i, tokensResult.size());
            return 1;
        }

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
