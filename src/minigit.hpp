#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <fmt/core.h>
#include <vector>
#include <fmt/core.h>
#include <fmt/color.h>

#include "hashgen.hpp"
#include "document.hpp"

namespace fs = std::filesystem;
using std::pair;
using std::vector;
using std::map;
using std::string;

class Minigit {
  static inline map<string, string> configmap;
  typedef pair<string, string> elem;

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
  static void help() {
    fmt::print("Usage: minigit [--version|-v] [--help|-h] <command>\n\nThese are common MiniGit commands used in various situations:\n\n");

    vector<elem> situation = {elem("clone", "Clone a repository into a new directory"),
      elem("init", "Create an empty Git repository or reinitialize an existing one")};
    printHelpDesc("start a working area", situation);

    situation = { elem("add", "Add file contents to the index"),
      elem("mv", "Move or rename a file, a directory, or a symlink"),
      elem("rm", "Remove files from the working tree and from the index")};
    printHelpDesc("work on the current change", situation);

    situation = { elem("diff", "Show changes between commits, commit and working tree, etc"),
      elem("log", "Show commit logs"),
      elem("show", "Show various types of objects"),
      elem("status", "Show the working tree status")};
    printHelpDesc("examine the history and state", situation);

    situation = { elem("commit", "Record changes to the repository"),
      elem("reset", "Reset current HEAD to the specified state") };
    printHelpDesc("grow, mark and tweak your common history", situation);
  }
private:
  static void printHelpDesc(string intro, const vector<elem>& situation) {
    fmt::print("{}\n", intro);
    for (elem e : situation) {
      fmt::print(fg(fmt::color::light_green), " {}", e.first);
      fmt::print("\t\t{}\n", e.second);
    }
    fmt::print("\n");
  }
};
