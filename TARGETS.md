# Bazel Targets Reference

## All Available Targets

### C Project Targets

#### Binaries
- `//c_project:c_app` - Main C application (executable)

#### Libraries
- `//c_project:math_utils` - Math utilities (add, multiply)
- `//c_project/string_utils:string_utils` - String manipulation utilities
- `//c_project/file_io:file_io` - File I/O operations
- `//c_project/data_structures:linked_list` - Linked list implementation
- `//c_project/data_structures:stack` - Stack implementation
- `//c_project/data_structures:data_structures` - Combined data structures (depends on linked_list + stack)

### C++ Project Targets

#### Binaries
- `//cpp_project:cpp_app` - Main C++ application (executable)

#### Libraries
- `//cpp_project:calculator` - Calculator with basic math operations
- `//cpp_project/logger:logger` - Logging utility with multiple log levels
- `//cpp_project/json_parser:json_parser` - Simple JSON parser
- `//cpp_project/json_parser:json_parser_with_nlohmann` - JSON parser using nlohmann/json (third-party)
- `//cpp_project/network:network` - Network client simulation

#### Tests (using Google Test)
- `//cpp_project/tests:calculator_test` - Unit tests for calculator
- `//cpp_project/tests:json_parser_test` - Unit tests for JSON parser
- `//cpp_project/tests:network_test` - Unit tests for network client
- `//cpp_project/tests:all_tests` - Test suite (runs all tests)

## Build Commands by Target Type

### Build Individual Libraries
```powershell
# C Libraries
.\bazel.exe build //c_project:math_utils
.\bazel.exe build //c_project/string_utils:string_utils
.\bazel.exe build //c_project/file_io:file_io
.\bazel.exe build //c_project/data_structures:linked_list
.\bazel.exe build //c_project/data_structures:stack

# C++ Libraries
.\bazel.exe build //cpp_project:calculator
.\bazel.exe build //cpp_project/logger:logger
.\bazel.exe build //cpp_project/json_parser:json_parser
.\bazel.exe build //cpp_project/json_parser:json_parser_with_nlohmann
.\bazel.exe build //cpp_project/network:network
```

### Build and Run Applications
```powershell
# Build only
.\bazel.exe build //c_project:c_app
.\bazel.exe build //cpp_project:cpp_app

# Build and run
.\bazel.exe run //c_project:c_app
.\bazel.exe run //cpp_project:cpp_app
```

### Run Tests
```powershell
# Run all tests
.\bazel.exe test //cpp_project/tests:all_tests

# Run individual tests
.\bazel.exe test //cpp_project/tests:calculator_test
.\bazel.exe test //cpp_project/tests:json_parser_test
.\bazel.exe test //cpp_project/tests:network_test

# Run with verbose output
.\bazel.exe test //cpp_project/tests:all_tests --test_output=all
```

### Build Everything
```powershell
# Build all targets in the workspace
.\bazel.exe build //...

# Build all C project targets
.\bazel.exe build //c_project/...

# Build all C++ project targets
.\bazel.exe build //cpp_project/...

# Run all tests
.\bazel.exe test //...
```

## Query Commands

### Show Dependencies
```powershell
# Show what c_app depends on
.\bazel.exe query "deps(//c_project:c_app)"

# Show what cpp_app depends on (with types)
.\bazel.exe query "deps(//cpp_project:cpp_app)" --output label_kind

# Show only direct dependencies
.\bazel.exe query "deps(//cpp_project:cpp_app, 1)"
```

### Show Reverse Dependencies
```powershell
# What depends on the calculator library?
.\bazel.exe query "rdeps(//..., //cpp_project:calculator)"

# What depends on string_utils?
.\bazel.exe query "rdeps(//..., //c_project/string_utils:string_utils)"
```

### Find Targets
```powershell
# List all targets
.\bazel.exe query //...

# List all test targets
.\bazel.exe query "kind(cc_test, //...)"

# List all library targets
.\bazel.exe query "kind(cc_library, //...)"

# List all binary targets
.\bazel.exe query "kind(cc_binary, //...)"
```

### Dependency Graph
```powershell
# Generate dependency graph (GraphViz format)
.\bazel.exe query --output graph "//cpp_project:cpp_app" > cpp_app_deps.dot

# You can visualize this with GraphViz:
# dot -Tpng cpp_app_deps.dot -o cpp_app_deps.png
```

## Target Naming Convention

Format: `//package_path:target_name`

- `//` - Repository root
- `package_path` - Path to the package (directory with BUILD file)
- `:` - Separator
- `target_name` - Name of the target defined in BUILD file

Examples:
- `//c_project:c_app` - Target "c_app" in package "c_project"
- `//cpp_project/logger:logger` - Target "logger" in package "cpp_project/logger"
- `//cpp_project/tests:all_tests` - Target "all_tests" in package "cpp_project/tests"

## Visibility Rules

### Public Visibility
Targets with `visibility = ["//visibility:public"]` can be used by any other target.

Examples:
- `//c_project:math_utils`
- `//cpp_project:calculator`

### Package Visibility
Targets with `visibility = ["//cpp_project:__subpackages__"]` can only be used within the same project.

Examples:
- `//c_project/string_utils:string_utils` - Only accessible by c_project packages
- `//cpp_project/logger:logger` - Only accessible by cpp_project packages

## External Dependencies

These third-party dependencies are automatically downloaded and built:

- `@com_google_googletest//:gtest_main` - Google Test framework
- `@nlohmann_json//:json` - nlohmann/json library
- `@com_google_absl//...` - Abseil C++ libraries (available but not yet used)

To use external dependencies, add them to the `deps` list in your BUILD file:
```python
cc_test(
    name = "my_test",
    srcs = ["my_test.cpp"],
    deps = [
        ":my_library",
        "@com_google_googletest//:gtest_main",
    ],
)
```
