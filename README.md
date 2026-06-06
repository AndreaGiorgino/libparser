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
