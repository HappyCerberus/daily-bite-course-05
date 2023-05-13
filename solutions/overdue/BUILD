filegroup(
    name = "data",
    srcs = glob(["data/**"]),
)

cc_library(
    name = "overdue",
    srcs = ["overdue.cc"],
    hdrs = ["overdue.h"],
)

cc_test(
    name = "overdue_test",
    srcs = ["overdue_test.cc"],
    data = [":data"],
    deps = [
        ":overdue",
        "@catch2//:catch2_main",
    ],
)
