#include <iostream>
#include <print>

#include "libparser/errors/file_error.hxx"
#include "libparser/parser.hxx"

using namespace libparser;

auto main(void) -> int {
    static constexpr auto filepath {"example.txt"};

    try {
        parser p {filepath};
        for (const auto& token : p.tokens())
            std::println(std::cout, "(position = {: >3}, literal = {:?})",
                token.position, token.literal);
    } catch (const errors::file_error& ex) {
        std::cerr << "parser file error: " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "unhandled exception: " << ex.what() << std::endl;
    }

    return 0;
}
