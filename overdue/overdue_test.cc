#include "catch2/catch_test_macros.hpp"
#include "overdue.h"

#include <filesystem>
#include <iostream>

TEST_CASE("Validate overdue") {
  using namespace std::literals;
  using namespace std::chrono;
  std::string runpath{getenv("TEST_SRCDIR")};
  std::filesystem::path data(runpath + "/_main/overdue/data/");

  auto nothing_overdue = sys_days{2023y / January / 4d};
  auto t1 = overdue_checkouts(data, nothing_overdue);
  REQUIRE(t1.size() == 0);

  auto january_first_overdue = sys_days{2023y / January / 1d} + 24h * 30 + 1s;
  auto t2 = overdue_checkouts(data, january_first_overdue);
  std::vector<OverdueInfo> expected2 = {
      {"Elizabeth Montgomery", "Benjamin Wilson", "The Silent Hills"},
      {"Elizabeth Montgomery", "Patricia Sanchez", "Shadows of the Past"},
      {"Elizabeth Montgomery", "Samuel Bennett", "The Final Hour"},
  };
  REQUIRE(std::is_permutation(t2.begin(), t2.end(), expected2.begin(),
                              expected2.end()));

  auto january_second_overdue = sys_days{2023y / January / 2d} + 24h * 30 + 1s;
  auto t3 = overdue_checkouts(data, january_second_overdue);
  std::vector<OverdueInfo> expected3 = {
      {"Elizabeth Montgomery", "Benjamin Wilson", "The Silent Hills"},
      {"Elizabeth Montgomery", "Patricia Sanchez", "Shadows of the Past"},
      {"Elizabeth Montgomery", "Samuel Bennett", "The Final Hour"},
      {"Michael Sullivan", "Emily Clark", "Lost in the Echo"},
      {"Michael Sullivan", "Benjamin Wilson", "The Silent Hills"}};
  REQUIRE(std::is_permutation(t3.begin(), t3.end(), expected3.begin(),
                              expected3.end()));

  auto january_third_overdue = sys_days{2023y / January / 3d} + 24h * 30 + 1s;
  auto t4 = overdue_checkouts(data, january_third_overdue);
  std::vector<OverdueInfo> expected4 = {
      {"Elizabeth Montgomery", "Benjamin Wilson", "The Silent Hills"},
      {"Elizabeth Montgomery", "Patricia Sanchez", "Shadows of the Past"},
      {"Elizabeth Montgomery", "Samuel Bennett", "The Final Hour"},
      {"Michael Sullivan", "Emily Clark", "Lost in the Echo"},
      {"Michael Sullivan", "Benjamin Wilson", "The Silent Hills"},
      {"Charles Johnson", "Michael Sullivan", "The Forgotten Kingdom"},
      {"Natalie Brooks", "Michael Sullivan", "The Forgotten Kingdom"}};
  REQUIRE(std::is_permutation(t4.begin(), t4.end(), expected4.begin(),
                              expected4.end()));
}