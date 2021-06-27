#pragma once
#include "file.hpp"
#include <chrono>

class Commit {
  //Informacion del usuario
  string sha1;
  int timestamp;
  list<File*> changes;
public:
  Commit(list<File*> stagingFiles) {
    changes = stagingFiles;
    timestamp = generateTimestamp(); //UNIX formato 
    sha1 = hash();
  }

  string getDiff() {
    return "";
  }

  string getSha1() {
    return "";
  }

  int getTimestamp() {
    return timestamp;
  }

  list<File*> getChanges() {
    return changes;
  }

private:
  int generateTimestamp() {
    const auto timeNow = chrono::system_clock::now();
    return chrono::duration_cast<chrono::seconds>(timeNow.time_since_epoch()).count();
  }

  string hash() {
    return "";
  }

};
