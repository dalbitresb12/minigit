#pragma once
#include "file.hpp"
#include "hashgen.hpp"
#include <fstream>

class Document : public File {
public:
  Document(string name, string path) : File(name, path) {}

  string getExt() {
    fs::path filePath = fs::path(path);
    return filePath.extension().generic_u8string();
  }

  string hash() {
    return HashGenerator::hash(getDocContent());
  }

  FileType getFileType() override {
    return FileType::Document;
  }

private:
  string getDocContent() {
    ifstream file(path);
    return string(istreambuf_iterator<char>(file),istreambuf_iterator<char>());
  }
};

