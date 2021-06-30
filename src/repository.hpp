#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <fmt/core.h>
#include <argparse/argparse.hpp>

#include "file.hpp"
#include "hashtable.hpp"
#include "commit.hpp"
#include "repositoryfinder.hpp"

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::fstream;
using std::ios;
using argparse::ArgumentParser;

class Repository {
  Commit* head;
  HashTable<Commit*> commits;

public:
  Repository(string ref) : commits(HashTable<Commit*>(30)) {
    fs::path refPath = RepositoryFinder::findRepository() / "refs/heads" / ref;
    if (!fs::exists(refPath)) {
      string err = fmt::format("fatal: cannot find the ref '{}'.", ref);
      throw std::invalid_argument(err);
    }
    string refHash;
    fstream refFile(refPath, ios::in);
    refFile >> refHash;
    head = new Commit(refHash);
  };
  void handleCommand(ArgumentParser& program, string command) {}
  void status();
  void add(vector<File*> files);
  void reset(vector<File*> files);
  void diff();
  void diff(string from, string to);
  void commit(string msg);
  void log();
  void log(string from, string to);
  void show(string hash);
  void rm(string path);
  void mv(string from, string to);
};
