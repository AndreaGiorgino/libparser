#include <format>

#include "libparser/parser.hxx"
#include "libparser/errors/file_error.hxx"

namespace fs = std::filesystem;

namespace libparser {
    parser::parser(std::string_view sourceFilePath) {
        if (sourceFilePath.empty())
            throw libparser::errors::file_error("Cannot use an empty path");

        _sourceFilePath = fs::absolute(sourceFilePath);
        if (!fs::exists(_sourceFilePath))
            throw libparser::errors::file_error(
                    std::format(
                        "Cannot find source file: {:?}",
                        _sourceFilePath.c_str()));
        else if (!fs::is_regular_file(_sourceFilePath))
            throw libparser::errors::file_error(
                    std::format(
                        "Cannot open non-regular file: {:?}",
                        _sourceFilePath.c_str()));

        _ifs = std::ifstream { _sourceFilePath };
        if (!_ifs)
            throw libparser::errors::file_error(
                    std::format(
                        "Cannot open file: {:?}",
                        _sourceFilePath.c_str()));
    }

    auto parser::get(void) -> token {
        if (_ifs.eof())
            return token { -1, std::string { (char)EOF } };
        else if (_ifs.tellg() == _bufferedToken.position) {
            _ifs.seekg(_bufferedToken.literal.size());
            return _bufferedToken;
        }

        _bufferedToken.position = _ifs.tellg();

        const auto ch { (char)_ifs.get() };
        _bufferedToken.literal = std::string { ch };

        if (ch == '\n')
            // newline
            return _bufferedToken;
        else if (std::isspace(ch)) {
            // space
            while (!_ifs.eof()
                    && std::isspace(_ifs.peek()))
                _bufferedToken.literal += (char)_ifs.get();
            return _bufferedToken;
        } else if (std::isalpha(ch)) {
            // alphanumeric
            while (!_ifs.eof()
                    && std::isalnum(_ifs.peek()))
                _bufferedToken.literal += (char)_ifs.get();
            return _bufferedToken;
        } else if (std::isdigit(ch)) {
            // numeric
            while (!_ifs.eof()
                    && std::isdigit(_ifs.peek()))
                _bufferedToken.literal += (char)_ifs.get();
            return _bufferedToken;
        }

        // symbol
        return _bufferedToken;
    }

    auto parser::peek(void) -> token {
        (void)get();

        _ifs.seekg(_bufferedToken.position);
        return _bufferedToken;
    }

    auto parser::ignore(size_t count) -> void {
        for (size_t i {}; i < count; i++)
            (void)get();
    }

    auto parser::tellg(void) -> std::streamoff {
        return _ifs.tellg();
    }

    auto parser::seekg(std::streamoff streamoff) -> void {
        _ifs.seekg(streamoff);
    }

    auto parser::eof(void) const -> bool {
        return _ifs.eof();
    }

    auto parser::tokens(void) -> std::generator<token> {
        while (!_ifs.eof())
            co_yield get();
    }
} // namespace 
