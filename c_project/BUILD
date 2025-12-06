# C Project BUILD file

cc_library(
    name = "math_utils",
    srcs = ["math_utils.c"],
    hdrs = ["math_utils.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "c_app",
    srcs = ["main.c"],
    deps = [
        ":math_utils",
        "//c_project/string_utils:string_utils",
        "//c_project/data_structures:linked_list",
        "//c_project/data_structures:stack",
    ],
)
