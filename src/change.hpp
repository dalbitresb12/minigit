#pragma once
#include "document.hpp"
#include "repository.hpp"

class Change {
  fs::path objPath;
  fs::path docPath;
  bool isDeleted;
public:
  Change(Document* doc = nullptr, bool isDeleted = false) {
    docPath = doc->getPath();
    genObjPath(doc->hash());
  }

  fs::path getObjPath() {
    return objPath;
  }

  fs::path getDocPath() {
    return docPath;
  }

private:
  void genObjPath(string docHash) {
    fs::path repoPath(Repository::findRepository() / "objects" / docHash.substr(0,2));
    if (!fs::exists(repoPath)) fs::create_directories(repoPath);
    
    objPath = repoPath / docHash.substr(2);
    if (!fs::exists(objPath)) fs::copy(docPath, objPath);
  }

};
