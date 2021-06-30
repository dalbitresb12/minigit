#pragma once

#include <filesystem>

#include "document.hpp"
#include "repository.hpp"

namespace fs = std::filesystem;

class Change {
  fs::path objectPath;
  fs::path documentPath;
  string documentHash;
  bool isDeleted;
public:
  Change(Document* document = nullptr, bool isDeleted = false) {
    documentPath = document->getPath();
    documentHash = document->hash();
    writeObject();
  }

  string getDocHash() {
    return documentHash;
  }

  void setDocPath(fs::path newpath) {
    documentPath = newpath;
  }

  fs::path getObjPath() {
    return objectPath;
  }

  fs::path getDocPath() {
    return documentPath;
  }

private:
  void writeObject() {
    fs::path path = Repository::findRepository() / "objects" / documentHash.substr(0, 2);
    if (!fs::exists(path))
      fs::create_directories(path);
    objectPath = path / documentHash.substr(2);
    if (!fs::exists(objectPath))
      fs::copy(documentPath, objectPath);
  }
};
