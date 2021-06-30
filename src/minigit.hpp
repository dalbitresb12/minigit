#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <fmt/core.h>

#include "hashgen.hpp"
#include "document.hpp"

namespace fs = std::filesystem;
using std::map;
using std::string;

class Minigit {
  static inline map<string, string> configmap;

  Minigit() {};
public:
  static string config(string key);
  static void config(string key, string value);
  static void init() {
    init(fs::current_path());
  };
  static void init(fs::path path) {
    fs::path repo = path / ".minigit";
    if (fs::exists(repo)) {
      fmt::print("Nothing was done, another repository already exists in this directory.\n");
      return;
    }
    fs::create_directories(repo);
    if (!fs::exists(repo)) {
      string err = fmt::format("fatal: cannot mkdir {}", repo.generic_u8string());
      throw std::runtime_error(err);
    }
    for (const string& dir : { "objects", "refs/heads" }) {
      fs::path dirPath = repo / dir;
      fs::create_directories(dirPath);
      if (!fs::exists(dirPath)) {
        string err = fmt::format("fatal: cannot mkdir {}", dirPath.generic_u8string());
        throw std::runtime_error(err);
      }
    }
    fmt::print("Initialized empty Git repository in {}\n", repo.generic_u8string());
  };
  static void hash(fs::path path) {
    Document* document = new Document(path);
    string* content = document->getContent();
    string hash = HashGenerator::hash(content);
    fmt::print("{}\n", hash);
  }
  static void clone(fs::path path);
};
