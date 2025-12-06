# Bazel workspace file for C/C++ project

workspace(name = "bazel_rbe")

# Load HTTP archive rule for fetching external dependencies
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Google Test - C++ testing framework
http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip"],
    strip_prefix = "googletest-1.14.0",
    sha256 = "1f357c27ca988c3f7c6b4bf68a9395005ac6761f034046e9dde0896e3aba00e4",
)

# nlohmann/json - JSON library for Modern C++
http_archive(
    name = "nlohmann_json",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz"],
    strip_prefix = "json",
    sha256 = "d6c65aca6b1ed68e7a182f4757257b107ae403032760ed6ef121c9d55e81757d",
    build_file = "@//:nlohmann_json.BUILD",
)

# Abseil - C++ common libraries
http_archive(
    name = "com_google_absl",
    urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20240116.2.tar.gz"],
    strip_prefix = "abseil-cpp-20240116.2",
    sha256 = "733726b8c3a6d39a4120d7e45ea8b41a434cdacde401cba500f14236c49b39dc",
)
