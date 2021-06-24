#include <file.hpp>
#include <filesystem>
namespace fs = std::filesystem;

class Folder : public File {
  list<File*> files;
public:
  Folder(string path, string name) : File(path, name) {}
  File* find(string searchPath) {
    string totalPath = getTotalPath(path, searchPath);
    if (fileExists(totalPath)) {
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
  bool fileExists(const fs::path& p, fs::file_status s = fs::file_status {}) {
    if (fs::status_known(s) ? fs::exists(s) : fs::exists(p)) return true;
    return false;
  }

  string getTotalPath(string initialPath, string searchPath) {
    string totalPath = initialPath;
    totalPath += "/";
    totalPath += searchPath;
    return totalPath;
  }
};

