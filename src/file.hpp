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
  File(string name, string path): name(name), path(path){
    fs::create_directories(path);
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
};
