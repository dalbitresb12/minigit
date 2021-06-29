#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>

#include "file.hpp"
#include "branch.hpp"
#include "branchmanager.hpp"
#include "stashmanager.hpp"

namespace fs = std::filesystem;
using std::string;
using std::vector;

class Repository {
  Branch* currentBranch;
  StashManager* stashmanager;
  BranchManager* branchmanager;
  static inline fs::path repositoryPath;
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
  void log(string from, string to);
  void hash(string path);
  void show(string hash);
  void rm(string path);
  void mv(string from, string to);
  StashManager* stash();
  void branch();
  void branch(string name);
  void checkout(string name, bool create = true);
  void merge(string name);

  static fs::path findRepository() {
   if (!repositoryPath.empty()) return repositoryPath;
   
   fs::path working_dir(fs::current_path());
   fs::path rootPath(working_dir.root_name() / working_dir.root_directory());
   while (!fs::exists(working_dir / fs::path(".minigit"))) {
     if (rootPath == working_dir) {
       throw std::runtime_error("No repository was found in parent directories.");
     }
     else if (fs::exists(working_dir.parent_path())) {
       working_dir = working_dir.parent_path();
     }
   }

   working_dir /= ".minigit";
   repositoryPath = working_dir;
   return working_dir;
  }
};
