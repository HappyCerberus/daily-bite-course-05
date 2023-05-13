filegroup(
    name = "data",
    srcs = glob(["data/**"]),
)

cc_library(
    name = "duplicates",
    srcs = ["duplicates.cc"],
    hdrs = ["duplicates.h"],
)

cc_test(
    name = "duplicates_test",
    srcs = ["duplicates_test.cc"],
    data = [":data"],
    deps = [
        ":duplicates",
        "@catch2//:catch2_main",
    ],
)
