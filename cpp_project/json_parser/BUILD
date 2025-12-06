# JSON Parser Submodule

cc_library(
    name = "json_parser",
    srcs = ["json_parser.cpp"],
    hdrs = ["json_parser.h"],
    visibility = ["//cpp_project:__subpackages__"],
)

# Alternative version using nlohmann/json (third-party dependency)
cc_library(
    name = "json_parser_with_nlohmann",
    srcs = ["json_parser_nlohmann.cpp"],
    hdrs = ["json_parser_nlohmann.h"],
    visibility = ["//cpp_project:__subpackages__"],
    deps = ["@nlohmann_json//:json"],
)
