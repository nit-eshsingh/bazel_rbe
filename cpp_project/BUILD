# C++ Project BUILD file

cc_library(
    name = "calculator",
    srcs = ["calculator.cpp"],
    hdrs = ["calculator.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "cpp_app",
    srcs = ["main.cpp"],
    deps = [
        ":calculator",
        "//cpp_project/logger:logger",
        "//cpp_project/json_parser:json_parser",
        "//cpp_project/json_parser:json_parser_with_nlohmann",
        "//cpp_project/network:network",
    ],
)
