#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "file.hpp"
#include "hashgen.hpp"

namespace fs = std::filesystem;
using std::string;
using std::ifstream;
using std::istreambuf_iterator;

class Document : public File {
  string* content;
  list<File*> versions;

public:
  Document(fs::path path) : File(path), content(nullptr) {}

  string getExt() {
    fs::path filePath = fs::path(path);
    return filePath.extension().generic_u8string();
  }

  string hash() {
    string* content = getContent();
    return HashGenerator::hash(content);
  }

  FileType getFileType() override {
    return FileType::Document;
  }

private:
  string* getContent() {
    if (content != nullptr) {
      return content;
    }

    ifstream file(path);
    return new string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
  }
};

