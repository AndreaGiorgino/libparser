# libparser

Parser library in c++.

> [!IMPORTANT]
> Since this library is still in development, it may not work correctly or some
> functionalities might be missing

## Build

### Requirements

- [CMake](https://cmake.org/)

### Compilation

```bash
git clone https://github.com/giorgi.page/libparser.git
cd libparser

cmake -B .build \
    && cmake --build .build --parallel $(($(nproc) - 1))
```

### Testing

```bash
cmake -B .build -DPARSER_BUILD_TESTING=ON \
    && cmake --build .build --parallel $(($(nproc) - 1)) \
    && ctest --test-dir .build
```

## Usage

```cpp
/*
 * main.cxx
 */

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
```

```cmake
#
# CMakeLists.txt
#

cmake_minimum_required(VERSION 3.24)

project(
    example
    LANGUAGES CXX
)

#
# Dependencies
#

include(FetchContent)

FetchContent_Declare(
    parser
    GIT_REPOSITORY git@github.com:AndreaGiorgino/libparser
    GIT_TAG 2.1.2
)

FetchContent_MakeAvailable(parser)

#
# Target
#

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(
    ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC parser
)
```
