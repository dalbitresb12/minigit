#pragma once

#include "hashtable.hpp"
#include "branch.hpp"

class BranchManager {
  HashTable<Branch*> branches;

public:
  BranchManager();
  ~BranchManager();
  void list();
  Branch* get(string name);
};
