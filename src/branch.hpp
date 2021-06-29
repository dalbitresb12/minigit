#pragma once

#include <string>
#include "hashtable.hpp"
#include "commit.hpp"

using std::string;

class Branch {
  string name;
  HashTable<Commit*> commits;

public:
  Branch();
  ~Branch();
  Commit* findCommit(string hash);
};
