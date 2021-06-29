#pragma once

#include <string>
#include "hashtable.hpp"
#include "commit.hpp"

class Branch {
  string name;
  HashTable<Commit*> commits;

public:
  Branch();
  ~Branch();
  Commit* findCommit(string hash);
};