#pragma once
#include <filesystem>
#include <string>
#include "file.hpp"

namespace fs = std::filesystem;
using std::string;
using std::list;

class Folder : public File {
  list<File*> files;
public:
  Folder(fs::path path) : File(path) {}

  File* find(fs::path searchPath) {
    fs::path totalPath = getTotalPath(path, searchPath);
    if (fs::exists(totalPath)) {
      fs::path fileName = totalPath.filename();
      // FALTA REEMPLAZAR LA BUSQUEDA FOR POR UNA DE ARBOLES
      for (File* file : files) {
        if (file->compareName(fileName)) return file;
      }
    }
    return nullptr;
  }

  bool contains(fs::path name) {
    if (compareName(name)) return true;
    // FALTA REEMPLAZAR LA BUSQUEDA FOR POR UNA DE ARBOLES
    for (File* file : files) {
      if (file->getFileType() == FileType::Document && file->compareName(name)) return true;
      else if (file->getFileType() == FileType::Folder) {
        Folder* folder = dynamic_cast<Folder*>(file);
        if (folder->contains(name)) return true;
      }
    }
    return false;
  }

  FileType getFileType() override {
    return FileType::Folder;
  }
private:
  fs::path getTotalPath(fs::path initialPath, fs::path searchPath) {
    return initialPath / searchPath;
  }
};

