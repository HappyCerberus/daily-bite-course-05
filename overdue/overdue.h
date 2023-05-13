#pragma once

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>

struct OverdueInfo {
  std::string user;
  std::string author;
  std::string book;
  bool operator==(const OverdueInfo &) const = default;
};

std::vector<OverdueInfo>
overdue_checkouts(std::filesystem::path db_path,
                  std::chrono::system_clock::time_point time);