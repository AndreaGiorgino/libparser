#include <array>
#include <format>
#include <iostream>

#include "libparser.hxx"
#include "errors/file_error.hxx"

static const auto testFilePath { "TestFiles/TestParseFile.txt" };
static const std::array<parser::token, 53> tokensResult {{
    { 1,   "#"      }, { 2,   "include" }, { 9,   " "    }, { 10,  "<"     },
    { 11,  "print"  }, { 16,  ">"       }, { 17,  "\n\n" }, { 19,  "auto"  },
    { 23,  " "      }, { 24,  "main"    }, { 28,  "("    }, { 29,  "int"   },
    { 32,  " "      }, { 33,  "argc"    }, { 37,  ","    }, { 38,  " "     },
    { 39,  "char"   }, { 43,  "*"       }, { 44,  "*"    }, { 45,  " "     },
    { 46,  "argv"   }, { 50,  ")"       }, { 51,  " "    }, { 52,  "-"     },
    { 53,  ">"      }, { 54,  " "       }, { 55,  "int"  }, { 58,  " "     },
    { 59,  "{"      }, { 60,  "\n    "  }, { 65,  "std"  }, { 68,  ":"     },
    { 69,  ":"      }, { 70,  "println" }, { 77,  "("    }, { 78,  "\""    },
    { 79,  "Hello"  }, { 84,  ","       }, { 85,  " "    }, { 86,  "world" },
    { 91,  "!"      }, { 92,  "\""      }, { 93,  ")"    }, { 94,  ";"     },
    { 95,  "\n    " }, { 100, "return"  }, { 106, " "    }, { 107, "0"     },
    { 108, ";"      }, { 109, "\n"      }, { 110, "}"    }, { 111, "\n"    },
    { -1, std::string { (char)EOF } },
}};

auto TestParseFile(int, char**) -> int {
    try {
        parser p { testFilePath };

        unsigned i {};
        for (const auto& token : p.tokens()) {
            if (i >= tokensResult.size())
                throw std::runtime_error(
                        std::format(
                            "-- Token index out of bounds: accessing index {} out of {} expected tokens.",
                            i, tokensResult.size()));
            if (const auto& tokenResult { tokensResult[i++] };
                    token.position != tokenResult.position
                        || token.literal != tokenResult.literal)
                throw std::runtime_error(
                        std::format(
                            "-- Token not matching the expected result: \"{{ {}, {:?} }}\" and \"{{ {}, {:?} }}\".",
                            token.position, token.literal,
                            tokenResult.position, tokenResult.literal));
        }
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    return 0;
}
