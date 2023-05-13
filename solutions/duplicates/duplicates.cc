#include "duplicates.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

/* \brief Check whether the content of two files matches. */
bool files_match(std::filesystem::path left_path,
                 std::filesystem::path right_path) {
  // open both files for reading
  std::ifstream left(left_path);
  std::ifstream right(right_path);

  // read character by character and compare
  int l = 0;
  int r = 0;
  while ((l = left.get()) == (r = right.get()) && !(left.eof() || right.eof()))
    ;
  // the files only match if both both reached end of file
  return left.eof() && right.eof();
}

std::vector<DuplicateInfo> find_duplicates(std::filesystem::path path) {
  // data structure that we will use to store information about duplicate files
  std::unordered_multimap<std::string, std::vector<std::filesystem::path>> db;

  // recursively explore the directory
  for (const auto &entry :
       std::filesystem::recursive_directory_iterator(path)) {
    // ignore non-files
    if (!entry.is_regular_file())
      continue;

    // all known unique files with this filename in our db
    auto [begin, end] = db.equal_range(entry.path().filename());

    // if there is none, then simply insert
    // unfortunately we have spell out the types for std::pair
    if (begin == end) {
      db.insert(std::pair<std::string, std::vector<std::filesystem::path>>{
          entry.path().filename(), {entry.path().lexically_relative(path)}});
      continue;
    }

    // there are some known files with this filename
    bool match = false;
    for (auto &[name, paths] : std::ranges::subrange(begin, end)) {
      // if the content matches, add it to the list
      if (files_match(path / paths[0], entry.path())) {
        // lexically_relative will not resolve symlinks
        paths.push_back(entry.path().lexically_relative(path));
        match = true;
        break;
      }
    }
    // there could be files with this filename, but not matching the content, in
    // such case, this is a new entry
    if (!match) {
      db.insert(std::pair<std::string, std::vector<std::filesystem::path>>{
          entry.path().filename(), {entry.path().lexically_relative(path)}});
    }
  }

  // convert our DB to std::vector<DuplicateInfo>
  std::vector<DuplicateInfo> result;
  for (auto &[k, v] : db) {
    if (v.size() > 1)
      result.push_back({k, v});
  }
  return result;
}