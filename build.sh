#!/user/bin/env bash

cmake -B build -DPARSER_BUILD_TESTING=ON \
    && cmake --build build --parallel $(($(nproc) - 1)) \
    && ctest --test-dir build 
