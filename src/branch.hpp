#pragma once

#include <string>
#include "hashtable.hpp"

class Branch {
  string name;
  HashTable<Commit*> commits;

public:
  Branch();
  ~Branch();
  Commit* findCommit(string hash);
};
