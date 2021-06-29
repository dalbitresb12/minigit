#pragma once
#include "file.hpp"
#include "user.hpp"
#include "hashgen.hpp"
#include "change.hpp"
#include "diffMethods.hpp"

#include <chrono>
#include <ctime>
#include <openssl/sha.h>

using std::string;

class Commit {
  //Informacion del usuario
  Commit* prevCommit;
  User* user;
  string subject;
  string sha1;
  int timestamp;
  list<Change*> changes;
public:

  Commit(Commit* prev = nullptr, User* user = nullptr, string subject = "") 
    : prevCommit(prev), user(user), subject(subject) {
    //list<File*> stagingFiles
    //changes = stagingFiles;
    timestamp = generateTimestamp(); 
    sha1 = HashGenerator::hash(commitToStr());
  }

  string getDiff() {
   
    DiffMeth::filediff("", "doc2.txt");

    for (Change* change : changes) {
      for (Change* prevChange : prevCommit->getChanges()) {
        if (change->getDocPath() == prevChange->getDocPath()) {
          DiffMeth::filediff(prevChange->getObjPath(), change->getObjPath());
          break;
        }
      }
      DiffMeth::filediff("", change->getObjPath());
    }


    //DiffMeth::strdiff("abcdefg", "abcdefg");
    return "";
  }

  string getSha1() {
    return sha1;
  }

  string getDate() {
    return epochConverter(getTimestamp());
  }

  string getSubject() {
    return subject;
  }

  int getTimestamp() {
    return timestamp;
  }

  list<Change*> getChanges() {
    return changes;
  }

  User* getUser() {
    return user;
  }

private:
  int generateTimestamp() {
    const auto timeNow = chrono::system_clock::now();
    return chrono::duration_cast<chrono::seconds>(timeNow.time_since_epoch()).count();
  }

  string commitToStr() {
    string commitStr = "From: " + user->getName() + " <" + user->getMail() + ">\n" +
      "Date: " + epochConverter(getTimestamp()) +
      "Subject: " + subject + "\n\n---\n";
      
      //+
      //getDiff();

    //cout << commitStr;

    return commitStr;
  }

  string epochConverter(int unixEpochTime) {
    time_t rawTime = unixEpochTime;
    return ctime(&rawTime);
  }

};
