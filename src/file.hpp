#pragma once
#include <list>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using std::string;
using std::list;

enum class FileType {
  Document,
  Folder
};

class File {
protected:
  fs::path path;
  fs::path name;
  list<File*> versions;

  File(fs::path path) : path(path) {
    name = path.filename();
  }

public:
  bool compareName(fs::path name) {
    return this->name == name;
  }

  virtual FileType getFileType() = 0;

  fs::path getPath() {
    return path;
  }

  fs::path getName() {
    return name;
  }
};
