#pragma once

/*
 * libparser - version 0.1.0
 */

#include <filesystem>
#include <generator>
#include <string>

class parser final {
    public: // definitions
        struct token final {
            std::streamoff position {};
            std::string literal {};
        };

    public: // ctors
        parser(std::string_view sourceFilePath);

        parser(const parser&) noexcept = default;
        auto operator =(const parser&) noexcept -> parser& = default;

        parser(parser&&) noexcept = default;
        auto operator =(parser&&) noexcept -> parser& = default;

        ~parser(void) noexcept = default;

    public: // methods
        [[nodiscard]]
            auto tokens(void) const -> std::generator<token>;

    private: // members
        std::filesystem::path _sourceFilePath {};
};
