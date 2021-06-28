#pragma once
#include <string>
class Branch {
  string name;
  HashTable<Commit*> commits;
public:
  Branch();
  ~Branch();
  Commit* findCommit(string hash);

};

