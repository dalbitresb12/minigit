#pragma once

#include <fstream>
#include <chrono>
#include <ctime>
#include <openssl/sha.h>
#include <fmt/core.h>
#include <fmt/chrono.h>

#include "file.hpp"
#include "user.hpp"
#include "hashgen.hpp"
#include "change.hpp"
#include "diffUtils.hpp"

namespace chrono = std::chrono;
using std::fstream;
using std::string;

class Commit {
  Commit* parent;
  User* user;
  string subject;
  string hash;
  int timestamp;
  list<Change*> changes;

public:
  Commit(list<Change*> changes, string subject = "", User* user = nullptr, Commit* parent = nullptr)
    : changes(changes), subject(subject), parent(parent), user(user) {
    timestamp = createTimestamp();
    string patch = getPatch();
    hash = HashGenerator::hash(patch);
    writeCommit(patch);
  }

  string getPatch() {
    string patch = createCommitHeader();

    if (parent != nullptr) {
      for (Change* change : changes) {
        bool didBreak = false;
        for (Change* prevChange : parent->changes) {
          if (change->getDocPath() == prevChange->getDocPath()) {
            patch += createPatchHeader(prevChange, change) +
              DiffUtils::unified(prevChange->getObjPath(), change->getObjPath());
            didBreak = true;
            break;
          }
        }
        if (didBreak) continue;
        patch += createPatchHeader(change, change) +
          DiffUtils::unified("", change->getObjPath());
      }
      return patch;
    }

    for (Change* change : changes) {
      patch += createPatchHeader(change, change) +
        DiffUtils::unified("", change->getObjPath());
    }
    return patch;
  }

  string getHash() {
    return hash;
  }

private:
  string createCommitHeader() {
    string header;
    if (parent != nullptr)
      header += fmt::format("Parent: {}\n", parent->hash);
    if (user != nullptr)
      header += fmt::format("From: {} <{}>\n", user->getName(), user->getEmail());
    header += fmt::format("Date: {}\n", createDateTime());
    header += fmt::format("Subject: [PATCH] {}\n", subject);
    return header + "\n---\n";
  }

  string createPatchHeader(Change* prev, Change* current) {
    string header;
    fs::path prevPath = createPathChange("a", prev);
    fs::path nextPath = createPathChange("b", current);

    header += fmt::format("diff {} {}\n", prevPath.generic_u8string(), nextPath.generic_u8string());
    header += createIndexComparer(prev, current);
    if (prev != current) header += fmt::format("--- {}\n", prevPath.generic_u8string());
    else header += "--- /dev/null\n";
    header += fmt::format("+++ {}\n", nextPath.generic_u8string());
    return header;
  }

  fs::path createPathChange(string prefix, Change* change) {
    return fs::path(prefix) / change->getDocPath();
  }

  string createIndexComparer(Change* fchange, Change* schange) {
    string indexA = fchange->getDocHash().substr(0, 7);
    string indexB = schange->getDocHash().substr(0, 7);

    if (indexA == indexB) indexA = "0000000";
    return fmt::format("index {}..{}\n", indexA, indexB);
  }

  int createTimestamp() {
    const auto now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();
  }

  string createDateTime() {
    time_t raw = timestamp;
    return fmt::format("{:%a, %e %b %Y %T %z}", fmt::localtime(raw));
  }

  void writeCommit(string patch) {
    fs::path path(Repository::findRepository() / "objects" / hash.substr(0, 2));
    if (!fs::exists(path)) fs::create_directories(path);
    fstream file(path / hash.substr(2), std::ios::out | std::ios::binary);
    file << patch;
  }
};
