#pragma once

/*
 * libparser - version 2.0.0
 */

#include <filesystem>
#include <generator>
#include <fstream>
#include <string>

class parser final {
    public: // definitions
        struct token final {
            std::streamoff position { -1 };
            std::string literal {};
        };

    public: // ctors
        parser(std::string_view sourceFilePath);

        parser(const parser&) noexcept = delete;
        auto operator =(const parser&) noexcept -> parser& = delete;

        parser(parser&&) noexcept = delete;
        auto operator =(parser&&) noexcept -> parser& = delete;

        ~parser(void) noexcept = default;

    public: // methods
        [[nodiscard]] auto get(void) -> token;
        [[nodiscard]] auto peek(void) -> token;
        auto ignore(size_t count = 1) -> void;

        [[nodiscard]] auto tellg(void) -> std::streamoff;
        auto seekg(std::streamoff streamoff) -> void;
        [[nodiscard]] auto eof(void) const -> bool;

        [[nodiscard]] auto tokens(void) -> std::generator<token>;

    private: // members
        std::filesystem::path _sourceFilePath {};
        std::ifstream _ifs {};
        token _bufferedToken {};
};
