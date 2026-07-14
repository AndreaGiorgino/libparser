#include <format>
#include <iostream>
#include <print>

#include "libparser/errors/file_error.hxx"
#include "libparser/parser.hxx"

#define ANSI_BOLD  "\033[1m"
#define ANSI_RESET "\033[0m"

using namespace libparser;

auto main(void) -> int {
    static constexpr auto filepath {"example.txt"};

    static constexpr auto posColWidth {4};

    static constexpr auto separatorWidth {30};
    static const std::string separator {
        std::format("{:->{}}", "", separatorWidth)};

    try {
        std::cout << separator << std::endl;
        std::println(ANSI_BOLD " {: <{}}" ANSI_RESET " | " ANSI_BOLD
                               "Literal" ANSI_RESET,
            "Pos", posColWidth);
        std::cout << separator << std::endl;

        parser p {filepath};

        for (const auto& token : p.tokens())
            std::println(
                " {: >{}} | {:?}", token.position, posColWidth, token.literal);

        std::cout << separator << std::endl;
    } catch (const libparser::errors::file_error& ex) {
        std::cerr << "tokenizer file error: " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "unhandled exception: " << ex.what() << std::endl;
    }

    return 0;
}
