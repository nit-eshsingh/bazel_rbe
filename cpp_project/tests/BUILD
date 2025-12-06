# Tests using Google Test (third-party dependency)

cc_test(
    name = "calculator_test",
    size = "small",
    srcs = ["calculator_test.cpp"],
    deps = [
        "//cpp_project:calculator",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "json_parser_test",
    size = "small",
    srcs = ["json_parser_test.cpp"],
    deps = [
        "//cpp_project/json_parser:json_parser",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "network_test",
    size = "small",
    srcs = ["network_test.cpp"],
    deps = [
        "//cpp_project/network:network",
        "@com_google_googletest//:gtest_main",
    ],
)

# Test suite that runs all tests
test_suite(
    name = "all_tests",
    tests = [
        ":calculator_test",
        ":json_parser_test",
        ":network_test",
    ],
)
