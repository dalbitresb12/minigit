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
  StashManager* stashManager;
  BranchManager* branchManager;
  static inline fs::path repositoryPath;

public:
  Repository() {
    
  };
  ~Repository() {
    if (currentBranch != nullptr) delete currentBranch;
    if (stashManager != nullptr) delete stashManager;
    if (branchManager != nullptr) delete branchManager;
  };
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

    fs::path workingDir(fs::current_path());
    fs::path rootPath(workingDir.root_name() / workingDir.root_directory());
    while (!fs::exists(workingDir / ".minigit")) {
      if (rootPath == workingDir) {
        throw std::runtime_error("fatal: not a git repository (or any of the parent directories): .minigit");
      } else if (fs::exists(workingDir.parent_path())) {
        workingDir = workingDir.parent_path();
      }
    }
    workingDir /= ".minigit";
    repositoryPath = workingDir;
    return workingDir;
  }
};
