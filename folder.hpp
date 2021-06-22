#include <file.hpp>

class Folder: public File {
  list<File*> files;
public:
  File* find(string path) {

  }

  bool contains(string name) override {
    if (files.empty()) return;
    for (File* file : files) {
      if (file->contains()) return true;
    }
    return false;
  }
};


