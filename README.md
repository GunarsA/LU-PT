# LU testing course

This repository contains a C++ implementation that finds all strongly connected components (SCCs) in a directed graph using depth-first search (DFS). The implementation relies on a two-pass DFS algorithm to efficiently identify SCCs.

## Features

- Efficient computation of SCCs in directed graphs.
- Utilizes a two-pass algorithm involving a normal and a reverse DFS.
- Outputs each SCC as a vector of nodes.

## Google Test

### Requirements

The **Google Test** is setup using **Bazel**. You can find the installation instructions at <https://google.github.io/googletest/quickstart-bazel.html>.

### Running the tests

To run the tests, you need to run the following command in the root directory of the project:

```bash
bazel test --cxxopt=-std=c++14 --test_output=all //:scc
```

[![asciicast](https://asciinema.org/a/F0nT5wXvpjeTuK4bWZn42kay2.svg)](https://asciinema.org/a/F0nT5wXvpjeTuK4bWZn42kay2)