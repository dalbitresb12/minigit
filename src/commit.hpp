#pragma once
#include "file.hpp"
#include "user.hpp"
#include "hashgen.hpp"
#include "change.hpp"
#include "diffMethods.hpp"

#include <fstream>
#include <chrono>
#include <ctime>
#include <openssl/sha.h>

namespace chrono = std::chrono;
using std::fstream;
using std::string;
using std::cout;

class Commit {
  //Informacion del usuario
  Commit* prevCommit;
  User* user;
  string subject;
  string sha1;
  int timestamp;
  list<Change*> changes;
public:

  Commit(list<Change*> changes, string subject = "",User* user = nullptr, Commit* prev = nullptr)
    : changes(changes), subject(subject), prevCommit(prev), user(user) {
    //list<File*> stagingFiles
    //changes = stagingFiles;
    timestamp = generateTimestamp();
    string patch = getPatch();
    sha1 = HashGenerator::hash(patch);
    genCommitPath(patch);
  }

  string getPatch() {
    string patch;
    patch = getCommitInfo() + "\n";

    if (prevCommit != nullptr) {
      for (Change* change : changes) {
        bool wasBroken = false;
        for (Change* prevChange : prevCommit->getChanges()) {
          if (change->getDocPath() == prevChange->getDocPath()) {
            patch += genHeaderPatch(prevChange, change) +
              DiffMeth::unifiedDiff(prevChange->getObjPath(), change->getObjPath());
            wasBroken = true;
            break;
          }
        }
        if (wasBroken) continue;
        patch += genHeaderPatch(change, change) + 
          DiffMeth::unifiedDiff("", change->getObjPath());
      }
    } else {
      for (Change* change : changes) {
        patch += genHeaderPatch(change, change) +
          DiffMeth::unifiedDiff("", change->getObjPath());
      }
    }
    return patch;
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

  string genHeaderPatch(Change* fchange, Change* schange) {
    string headerPatch;

    string strDocPathA = "a/" + fchange->getDocPath().generic_u8string();
    string strDocPathB = "b/" + schange->getDocPath().generic_u8string();

    headerPatch += "diff " + strDocPathA + " " + strDocPathB + "\n";
    headerPatch += indexComparer(fchange, schange);


    if (fchange != schange) headerPatch += "--- " + strDocPathA + "\n";
    else headerPatch += "--- /dev/null\n";
    headerPatch +=  "+++ " + strDocPathB + "\n";

    return headerPatch;
  }

  string indexComparer(Change* fchange, Change* schange) {
    string indexA = fchange->getDocHash().substr(0, 7);
    string indexB = schange->getDocHash().substr(0, 7);

    if (indexA == indexB) indexA = "0000000";
    return "index " + indexA  + ".." +  indexB + "\n";
  }

  int generateTimestamp() {
    const auto timeNow = chrono::system_clock::now();
    return chrono::duration_cast<chrono::seconds>(timeNow.time_since_epoch()).count();
  }

  string getCommitInfo() {
    string commitInfo = "";
    
    if (user != nullptr) commitInfo += "From: " + user->getName() + " <" + user->getMail() + ">\n";
    commitInfo += "Date: " + epochConverter(getTimestamp()) + "Subject: " + subject + "\n\n---";
    return commitInfo;
  }

  string epochConverter(int unixEpochTime) {
    time_t rawTime = unixEpochTime;
    return ctime(&rawTime);
  }
  
  void genCommitPath(string patch) {
    fs::path repoPath(Repository::findRepository() / "temp" / sha1.substr(0, 2));
    if (!fs::exists(repoPath)) fs::create_directories(repoPath);
    fstream commitFile(repoPath / sha1.substr(2), std::ios::out|std::ios::binary);
    commitFile << patch;
    
  }
};
