#pragma once

#include <string>
#include <vector>

#include "file.hpp"
#include "branch.hpp"
#include "branchmanager.hpp"
#include "stashmanager.hpp"

  using std::string;
  using std::vector;

class Repository {
  Branch* branch;
  StashManager* stashmanager;
  BranchManager* branchmanager;

public:
  Repository();
  ~Repository();
  void status();
  void add(vector<File*> files);
  void reset(vector<File*> files);
  void diff();
  void diff(string from, string to);
  void commit(string msg);
  void log();
  void log(strin from, string to);
  void hash(string path);
  void show(string hash);
  void rm(string path);
  void mv(string from, string to);
  StashManager* stash();
  void branch();
  void branch(string name);
  void checkout(string name, bool create = true);
  void merge(string name);
};
