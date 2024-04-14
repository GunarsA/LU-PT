# LU testing course

## Google Test

### Requirements

The **Google Test** is setup using **Bazel**. You can find the installation instructions at <https://google.github.io/googletest/quickstart-bazel.html>.

### Running the tests

To run the tests, you need to run the following command in the root directory of the project:

```bash
bazel test --cxxopt=-std=c++14 --test_output=all //:scc
```

<script src="https://asciinema.org/a/F0nT5wXvpjeTuK4bWZn42kay2.js" id="asciicast-654118" async="true"></script>