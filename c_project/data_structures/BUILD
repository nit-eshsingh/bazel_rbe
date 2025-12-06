# Data Structures Submodule

cc_library(
    name = "linked_list",
    srcs = ["linked_list.c"],
    hdrs = ["linked_list.h"],
    visibility = ["//c_project:__subpackages__"],
)

cc_library(
    name = "stack",
    srcs = ["stack.c"],
    hdrs = ["stack.h"],
    visibility = ["//c_project:__subpackages__"],
)

cc_library(
    name = "data_structures",
    visibility = ["//c_project:__subpackages__"],
    deps = [
        ":linked_list",
        ":stack",
    ],
)
