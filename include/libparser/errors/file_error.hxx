#pragma once

#include <string>

namespace libparser::errors {
    /**
     * @class file_error
     * @brief Represents a file error
     *
     */
    class file_error final : public std::exception {
        public: // ctors
            file_error(std::string_view errorMessage = "Unknown error") noexcept;

            file_error(const file_error&) = default;
            auto operator =(const file_error&) -> file_error& = default;

            file_error(file_error&&) = default;
            auto operator =(file_error&&) -> file_error& = default;

            ~file_error(void) = default;

        public:
            /**
             * @brief Get the error message
             */
            auto what(void) const noexcept -> const char* override;

        private:
            std::string _errorMessage {};
    };
} // namespace libparser::errors
