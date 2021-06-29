#pragma once
#include <list>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

enum class FileType {
  Document,
  Folder
};

class File {
protected:
  string path;
  string name;
  list<File*> versions;
  File(string path): path(path){
    name = pathToName(path);
  }
public:
  bool compareName(string name) {
    return this->name == name;
  }

  virtual FileType getFileType() = 0;

  string getPath() {
    return path;
  }

  string getName() {
    return name;
  }
protected:
  string pathToName(string path) {
    return fs::path(path).filename().generic_u8string();
  }
};
