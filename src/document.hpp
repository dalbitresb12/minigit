#pragma once
#include "file.hpp"
#include "hashgen.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using std::string;
using std::ifstream;
using std::istreambuf_iterator;

class Document : public File {
public:
  Document(fs::path path) : File(path) {}

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

