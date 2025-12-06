# Automotive Module - Main BUILD file

cc_binary(
    name = "automotive_app",
    srcs = ["automotive_main.c"],
    deps = [
        "//c_project/automotive/clutch:clutch",
        "//c_project/automotive/brake:brake",
        "//c_project/automotive/gear:gear",
        "//c_project/automotive/ev:ev_battery",
        "//c_project/automotive/powertrain:powertrain",
    ],
)

# Aggregate library for all automotive components
cc_library(
    name = "automotive_all",
    visibility = ["//visibility:public"],
    deps = [
        "//c_project/automotive/clutch:clutch",
        "//c_project/automotive/brake:brake",
        "//c_project/automotive/gear:gear",
        "//c_project/automotive/ev:ev_battery",
        "//c_project/automotive/powertrain:powertrain",
    ],
)
