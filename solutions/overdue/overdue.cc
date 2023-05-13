#include "overdue.h"
#include <fstream>
#include <unordered_map>

struct Book {
  std::string author;
  std::string title;
};

std::vector<OverdueInfo>
overdue_checkouts(std::filesystem::path db_path,
                  std::chrono::system_clock::time_point time) {
  using namespace std::literals;

  // read the users_db.txt
  std::unordered_map<int64_t, std::string> users;
  {
    std::ifstream f(db_path / "users_db.txt"s);
    int64_t id = 0;
    std::string name;
    while (f >> id >> std::quoted(name))
      users.insert_or_assign(id, name);
  }

  // read the books_db.txt
  std::unordered_map<int64_t, Book> books;
  {
    std::ifstream f(db_path / "books_db.txt"s);
    int64_t id = 0;
    std::string author;
    std::string title;
    while (f >> id >> std::quoted(author) >> std::quoted(title))
      books.insert_or_assign(id, Book{author, title});
  }

  std::vector<OverdueInfo> result;
  // Now process the checkouts_db, adding overdue books into result
  {
    std::ifstream f(db_path / "checkouts_db.txt"s);
    int64_t book_id;
    int64_t user_id;
    int64_t since_epoch;
    while (f >> book_id >> user_id >> since_epoch) {
      // since_epoch is a raw number, *1s produces seconds (a duration)
      // time_point can be initialized using a duration since epoch
      std::chrono::system_clock::time_point t(since_epoch * 1s);
      // note that 30d is not 30 days, but the 30th day of a month
      if (time - t < 30 * 24h)
        continue;
      result.push_back(
          {users[user_id], books[book_id].author, books[book_id].title});
    }
  }
  return result;
}