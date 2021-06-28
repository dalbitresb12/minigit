#pragma once
class BranchManager {
  HashTable<Branch*> branches;
public:
  BranchManager();
  ~BranchManager();
  void list();
  Branch* get(string name);

};
