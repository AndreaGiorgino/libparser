#pragma once

/*
 * libparser - version 2.0.0
 */

#include <filesystem>
#include <generator>
#include <fstream>
#include <string>

namespace libparser {
    /**
     * @class parser
     * @brief Represents the parser
     *
     */
    class parser final {
        public: // definitions
            /**
             * @class token
             * @brief Represents the parsed part
             *
             */
            struct token final {
                std::streamoff position { -1 };
                std::string literal {};
            };

        public: // ctors
            parser(std::string_view sourceFilePath);

            parser(const parser&) = delete;
            auto operator =(const parser&) = delete;

            parser(parser&&) = delete;
            auto operator =(parser&&) = delete;

            ~parser(void) = default;

        public: // methods
            /**
             * @brief Get the next token
             */
            [[nodiscard]]
                auto get(void) -> token;

            /**
             * @brief Peek the next token
             */
            [[nodiscard]]
                auto peek(void) -> token;

            /**
             * @brief Ignore the next tokens
             *
             * @param count The count of tokens to ignore
             */
            auto ignore(size_t count = 1) -> void;

            /**
             * @brief Get the stream offset of the file being parsed
             */
            [[nodiscard]]
                auto tellg(void) -> std::streamoff;

            /**
             * @brief Set the stream offset of the file being parsed
             *
             * @param streamoff The offset to set the file stream to
             */
            auto seekg(std::streamoff streamoff) -> void;

            /**
             * @brief Get if the file stream has reached eof
             */
            [[nodiscard]]
                auto eof(void) const -> bool;

            /**
             * @brief Get the tokens in a sequence
             */
            [[nodiscard]]
                auto tokens(void) -> std::generator<token>;

        private: // members
            std::filesystem::path _sourceFilePath {};
            std::ifstream _ifs {};
            token _bufferedToken {};
    };
} // namespace libparser
