# cmake-cmocka-template

Simple project to serve as a starting point for new C projects looking to use [Cmocka](https://cmocka.org/) for unit testing.

Features:

- Fetches CMocka and builds it for you.
  - Use Cmake option `ENABLE_TESTS` like so: `-DENABLE_TESTS=on`.
  - You can customize some options, for example, whether to build CMocka as a shared or static library, in the [FetchCMocka file](./cmake/Modules/FetchCMocka.cmake).
- Supports generation of coverage reports:
  - Use Cmake option `ENABLE_COVERAGE` like so: `-DENABLE_COVERAGE=on`.
  - Note that tests must be enabled as aswell.
  - Enabling coverage reports, using [GCovr](https://gcovr.com/en/stable/index.html), will compile the software with the following flags: `-g -O0 --coverage`.
- Sets up [cppcheck](http://cppcheck.net/) and [Clang-Tidy](https://clang.llvm.org/extra/clang-tidy/).
- Adds a CMake function to make it easier to wrap mocks. See the [test CMakeLists](./test/CMakeLists.txt) and the available [tests](./tests) for examples of what is possible.

Notes:

- Version 1.1.5 and bellow of CMocka build output has a different name for static libs, so you might need to change other stuff; also you should have no reason to downgrade CMocka's version.
- For details about the `--wrap` options that CMocka uses for mocks, see the [compiler documentation page](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_node/ld_3.html).

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run tests

```bash
cmake -DENABLE_TESTS=on ..
cmake --build .
ctest --verbose
```

## Get coverage report

```bash
cmake -DENABLE_TESTS=on -DENABLE_COVERAGE=on ..
cmake --build .
ctest --verbose
# need to run ctest first
make coverage

# See HTML version of the coverage report:
firefox coverage.html
```
