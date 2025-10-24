# m3u_prefix

A cli tool to replace text from different files and directories


## Build

This project can be built with Make:
```bash
# Development version
make

# Release version compiled with optimizations
make release
```

To clean build artifacts:
```bash
make clean
```

Requirements:
- C99-compatible compiler (GCC, Clang)
- Make build system

## Usage

``` bash

./m3u_prefix <path/to/m3u> <replacing string> <path/to/music/dir>
```
