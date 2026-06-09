#include <format>
#include <fstream>

#include "parser.hxx"
#include "errors/file_error.hxx"

namespace fs = std::filesystem;

parser::parser(std::string_view sourceFilePath) {
    if (sourceFilePath.empty())
        throw errors::file_error("Cannot use an empty path");

    _sourceFilePath = fs::absolute(sourceFilePath);
    if (!fs::exists(_sourceFilePath))
        throw errors::file_error(
                std::format(
                    "Cannot find source file: {:?}",
                    _sourceFilePath.c_str()));
    else if (!fs::is_regular_file(_sourceFilePath))
        throw errors::file_error(
                std::format(
                    "Cannot open non-regular file: {:?}",
                    _sourceFilePath.c_str()));
}

auto parser::tokens(void) const -> std::generator<token> {
    std::ifstream ifs { _sourceFilePath.c_str() };
    if (!ifs)
        throw errors::file_error(
                std::format(
                    "Cannot open file: {:?}",
                    _sourceFilePath.c_str()));

    while (true) {
        if (ifs.eof())
            break;

        const auto ch = (char)ifs.get();
        token ret { ifs.tellg(), std::string { ch } };

        if (ch == '\n') {
            co_yield ret;
            continue;
        } else if (std::isspace(ch)) {
            while (!ifs.eof()
                    && std::isspace(ifs.peek()))
                ret.literal += (char)ifs.get();
            co_yield ret;
            continue;
        } else if (std::isalpha(ch)) {
            while (!ifs.eof()
                    && std::isalnum(ifs.peek()))
                ret.literal += (char)ifs.get();
            co_yield ret;
            continue;
        } else if (std::isdigit(ch)) {
            while (!ifs.eof()
                    && std::isdigit(ifs.peek()))
                ret.literal += (char)ifs.get();
            co_yield ret;
            continue;
        } else if ((int)ifs.peek() == EOF)
            break;

        co_yield ret;
    };

    co_yield token { ifs.tellg(), std::string { (char)EOF } };
}
