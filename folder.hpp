#include <file.hpp>

class Folder : public File {
  list<File*> files;
public:
  Folder(string name, string path) : File(name, path) {}
  File* find(string searchPath) {
    string totalPath = getTotalPath(path, searchPath);
    if (fs::exists(totalPath)) {
      string fileName = fs::path(totalPath).filename().generic_u8string();
      // FALTA REEMPLAZAR LA BUSQUEDA FOR POR UNA DE ARBOLES
      for (File* file : files) {
        if (file->compareName(fileName)) return file;
      }
    }
    return nullptr;
  }

  bool contains(string name) {
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
  string getTotalPath(string initialPath, string searchPath) {
    return initialPath + "/" + searchPath;
  }
};

