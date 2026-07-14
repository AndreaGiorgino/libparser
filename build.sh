#!/usr/bin/env bash

cmake -B build \
    -DPARSER_BUILD_TESTING=ON \
    -DPARSER_BUILD_EXAMPLE=ON \
    && cmake --build build --parallel $(($(nproc) - 1)) \
    && ctest --test-dir build 
