#include <iostream>

#include "libparser/errors/file_error.hxx"
#include "libparser/parser.hxx"

using namespace libparser;

auto main(void) -> int {
    static constexpr auto filepath {"example.txt"};

    try {
        parser p {filepath};
        for (const auto& token : p.tokens())
            std::cout << "{"
                      << "\n  .position = " << token.position
                      << "\n  .literal  = " << std::quoted(token.literal)
                      << "\n}" << std::endl;
    } catch (const errors::file_error& ex) {
        std::cerr << "parser file error: " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "unhandled exception: " << ex.what() << std::endl;
    }

    return 0;
}
