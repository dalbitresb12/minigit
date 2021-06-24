#include <file.hpp>
#include <filesystem>
namespace fs = std::filesystem;

class Folder : public File {
  list<File*> files;
public:
  Folder(string path, string name) : File(path, name) {}
  File* find(string path) {

    return nullptr;
  }

  bool contains(string name) {
    if (compareName(name)) return true;
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
};

