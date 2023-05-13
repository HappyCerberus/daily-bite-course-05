#include "catch2/catch_test_macros.hpp"
#include "duplicates.h"

#include <filesystem>
#include <iostream>

TEST_CASE("Verify duplicates") {
  using namespace std::literals;
  std::string runpath{getenv("TEST_SRCDIR")};
  std::filesystem::path data(runpath + "/_main/solutions/duplicates/data/");
  std::vector<DuplicateInfo> expected{
      {"file2.txt"s, {{"02/file2.txt"s, "03/file2.txt"s}}},
      {"file2.txt"s, {{"04/file2.txt"s, "05/file2.txt"s}}},
      {"file1.txt"s, {{"file1.txt"s, "02/file1.txt"s}}}};

  auto duplicates = find_duplicates(data);
  REQUIRE(duplicates.size() == 3);

  for (auto &e : expected) {
    bool matched = false;
    for (auto &d : duplicates) {
      if (e.filename != d.filename)
        continue;
      if (std::is_permutation(e.duplicates.begin(), e.duplicates.end(),
                              d.duplicates.begin(), d.duplicates.end()))
        matched = true;
    }
    REQUIRE(matched);
  }
}