#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct DuplicateInfo {
  std::string filename;
  std::vector<std::filesystem::path> duplicates;
};

/* \brief Find sets of duplicate files.

A duplicate file has the same filename and the same content.
Each returned record contains the filename and a complete set filepaths to files
with duplicate content (and same filename).

Reported filepaths are relative to the provided directory.
*/
std::vector<DuplicateInfo> find_duplicates(std::filesystem::path directory);