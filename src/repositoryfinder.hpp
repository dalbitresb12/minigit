#pragma once

#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

class RepositoryFinder {
  static inline fs::path path;

public:
  static fs::path findRepository() {
    if (!path.empty()) return path;

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
    path = workingDir;
    return workingDir;
  }
};
