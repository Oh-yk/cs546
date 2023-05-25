load("//transpiler:fhe.bzl", "fhe_cc_library")

fhe_cc_library(
    name = "knn_tfhe",
    src = "knn.cc",
    hdrs = ["knn.h"],
)

cc_binary(
    name = "knn_client",
    srcs = [
        "knn.h",
        "info.h",
        "info.cc",
    ],
    deps = [
        ":knn_tfhe",
        "//transpiler/data:tfhe_data",
        "@com_google_absl//absl/base",
        "@com_google_xls//xls/common/logging",
        "@com_google_xls//xls/common/status:status_macros",
        "@tfhe//:libtfhe",
)