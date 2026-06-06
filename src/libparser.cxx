#include <format>
#include <fstream>

#include "libparser.hxx"
#include "errors/file_error.hxx"

namespace fs = std::filesystem;

parser::parser(std::string_view sourceFilePath) :
    _sourceFilePath(fs::absolute(sourceFilePath)) {
        if (sourceFilePath.empty())
            throw errors::file_error("Cannot use an empty path.");
        else if (!fs::exists(_sourceFilePath))
            throw errors::file_error(
                    std::format(
                        "Cannot find source file: {:?}.",
                        _sourceFilePath.c_str()));
        else if (!fs::is_regular_file(_sourceFilePath))
            throw errors::file_error(
                    std::format(
                        "Cannot open non-regular file: {:?}.",
                        _sourceFilePath.c_str()));
    }

auto parser::tokens(void) const -> std::generator<token> {
    std::ifstream streamIn { _sourceFilePath.c_str() };
    if (!streamIn)
        throw errors::file_error(
                std::format(
                    "Cannot open file: {:?}",
                    _sourceFilePath.c_str()));

    while (true) {
        if (streamIn.eof())
            break;

        const auto ch = (char)streamIn.get();
        token ret { streamIn.tellg(), std::string { ch } };

        if (std::isspace(ch)) {
            while (!streamIn.eof()
                    && std::isspace(streamIn.peek()))
                ret.literal += (char)streamIn.get();
            co_yield ret;
            continue;
        } else if (std::isalpha(ch)) {
            while (!streamIn.eof()
                    && std::isalnum(streamIn.peek()))
                ret.literal += (char)streamIn.get();
            co_yield ret;
            continue;
        } else if (std::isdigit(ch)) {
            while (!streamIn.eof()
                    && std::isdigit(streamIn.peek()))
                ret.literal += (char)streamIn.get();
            co_yield ret;
            continue;
        } else if ((int)streamIn.peek() == EOF)
            break;
    };

    co_yield token { streamIn.tellg(), std::string { (char)EOF } };
}
