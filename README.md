# Modern-Only C++ Course - Homework

This repository contains the homework for Lesson 5.

## Overdue books

Implement a function `overdue_checkouts` (in the file `overdue/overdue.cc`) that processes three database files containing information about users, books and book checkouts and returns a list of checkouts that are currently overdue for return.

Each book can be checked out for 30 days.

User db is in file `users_db.txt`, has one record per line, with each record consisting of a unique id (integer) and a quoted name of the user (separated by space).

Books db is in file `books_db.txt`, has one record per line, with each record consisting of a unique id (integer), a quoted name of the author and a quoted title of the book (separated by space).

Checkouts db is in file `checkouts_db.txt`, has one record per line, with each record consisting of the book id, user id and a timestamp representing seconds since epoch in UTC (separated by space).


```
bazel test //overdue/...
bazel test --config=addrsan //overdue/...
bazel test --config=ubsan //overdue/...
```

## Duplicate file finder

Implement a function `find_duplicates` (in the file `duplicates/duplicates.cc`) that finds duplicate files, i.e. files with the same filename and content. The function should return a `std::vector<DuplicateInfo>`, where each record corresponds to one set of duplicates.

The returned paths should be relative to path the `find_duplicates` function was called with.

The goal is to have the following commands pass without any errors:

```
bazel test //duplicates/...
bazel test --config=addrsan //duplicates/...
bazel test --config=ubsan //duplicates/...
```

### Tips

You will need to do a bit of searching on https://cppreference.com.

We did not talk about relative paths (there is a solution, but it isn't the obvious one).

There is data structure adjacent to `std::unordered_map` that you will find useful.

## Fun with sorting (freeform)

This homework doesn't have an associated test suite or example solution.

Have some fun with sorts: https://en.wikipedia.org/wiki/Sorting_algorithm. 

I have prepared a simple binary scafolding for you in the directory `sortingfun`. You can run the resulting executable using:

```
bazel run //sortingfun
```

Some ideas for you:

- implement a couple of basic sorts, you can put each of them into a separate namespace, or even a separate header/implementation file (follow the other homework as template to construct the BUILD file)

- measure using `std::chrono` how the performance differs across the different algorithms

- try different sizes of inputs

- try different containers (`std::vector`, `std::array`, `std::list`)

- try special types of inputs (already sorted, sorted in oposite direction, almost sorted, rotated)

Tips:

You can fill a container with consecutive numbers using the following snippet:

```
#include <algorithm>
#include <ranges>
#include <vector>
#include <cstdint>

std::vector<int64_t> data;
std::ranges::copy(
    std::views::iota(1,32), // 1..31
    std::back_inserter(data));
```

You can randomly shuffle a container using the following snippet:

```
#include <algorithm>
#include <vector>
#include <cstdint>
#include <random>

std::vector<int64_t> data{...};

// The number passed-in is the seed.
// Change it to change the order of elements.
std::default_random_engine engine(0);
std::shuffle(data.begin(), data.end(), engine);
```

## Solutions

If you wish to have a look at the solutions, you can find the commented code in the `solutions` directory.