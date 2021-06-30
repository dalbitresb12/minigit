#pragma once

#include <map>
#include <string>
#include <vector>
#include <fmt/core.h>
#include <fmt/color.h>

using std::pair;
using std::vector;
using std::map;
using std::string;

class Minigit {
  typedef pair<string, string> elem;
  map<string, string> configmap;

public:
  Minigit(){}
  ~Minigit();
  string config(string key);
  void config(string key, string value);
  void init();
  void init(string path);
  void clone(string path);
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
