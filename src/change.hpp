#pragma once
#include "document.hpp"
#include "repository.hpp"
#include <filesystem>

namespace fs = std::filesystem;

class Change {
  fs::path objPath;
  fs::path docPath;
  string docHash;
  bool isDeleted;
public:
  Change(Document* doc = nullptr, bool isDeleted = false) {
    docPath = doc->getPath();
    docHash = doc->hash();
    genObjPath();
  }

  string getDocHash() {
    return docHash;
  }

  void setDocPath(fs::path newpath) {
    docPath = newpath;
  }

  fs::path getObjPath() {
    return objPath;
  }

  fs::path getDocPath() {
    return docPath;
  }

private:
  void genObjPath() {
    fs::path repoPath(Repository::findRepository() / "objects" / docHash.substr(0,2));
    if (!fs::exists(repoPath)) fs::create_directories(repoPath);
    
    objPath = repoPath / docHash.substr(2);
    if (!fs::exists(objPath)) fs::copy(docPath, objPath);
  }

};
