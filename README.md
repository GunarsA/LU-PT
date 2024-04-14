# LU testing course

## Information

Running `main.cpp` will execute self made unit tests for the function inside `function.h`.

## Google Test

### Requirements

The **Google Test** is setup using **Bazel**. You can find the installation instructions at <https://google.github.io/googletest/quickstart-bazel.html>.

### Running the tests

To run the tests, you need to run the following command in the root directory of the project:

```bash
bazel test --cxxopt=-std=c++14 --test_output=all //:scc
```
