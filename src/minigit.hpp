#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <fmt/core.h>

namespace fs = std::filesystem;
using std::map;
using std::string;

class Minigit {
  map<string, string> configmap;

public:
  Minigit() {};
  string config(string key);
  void config(string key, string value);
  void init() {
    init(fs::current_path());
  };
  void init(fs::path path) {
    fs::path repo = path / ".minigit";
    fs::create_directories(repo);
    if (!fs::exists(repo)) {
      string err = fmt::format("fatal: cannot mkdir {}", repo.generic_u8string());
      throw std::runtime_error(err);
    }
    for (const string& dir : { "objects", "refs" }) {
      fs::path dirPath = repo / dir;
      fs::create_directory(dirPath);
      if (!fs::exists(dirPath)) {
        string err = fmt::format("fatal: cannot mkdir {}", dirPath.generic_u8string());
        throw std::runtime_error(err);
      }
    }
    fmt::print("Initialized empty Git repository in {}", repo.generic_u8string());
  };
  void clone(fs::path path);
};
