#include <file.hpp>

class Document : public File {
public:
  Document(string path, string name) : File(path, name) {}

  string getExt() {
    fs::path filePath = fs::path(this.path);
    return filePath.extension().generic_u8string();
  }

  string hash() {
    //Falta agregar librería para hallar el hash
    return "";
  }

  FileType getFileType() override {
    return FileType::Document;
  }
};

