#include "document.hpp"

class Change {
  string objPath;
  string docPath;
  bool isDeleted;
public:
  Change(Document* doc = nullptr, bool isDeleted = false) {
    docPath = doc->getPath();
    genObjPath(doc->hash());
  }

  string getObjPath() {
    return objPath;
  }

  string getDocPath() {
    return docPath;
  }

private:
  void genObjPath(string docHash) {



    cout << (isRepository() ? "true" : "false");

    if (!isRepository()) exit(1);



    string newObjPath = ".minigit/objects/" + docHash.substr(0, 2);
    if (!fs::exists(newObjPath)) fs::create_directories(newObjPath);
    
    objPath = newObjPath + "/" + docHash.substr(2);
    if(!fs::exists(objPath)) fs::copy(docPath, objPath);
  }

  bool isRepository() {
    fs::path working_dir(fs::current_path());
    fs::path rootPath(working_dir.root_name() / working_dir.root_directory());
    while (!fs::exists(working_dir / fs::path(".minigit"))) {
      if (rootPath == working_dir) return false;
      else if (fs::exists(working_dir.parent_path())) {
        working_dir = working_dir.parent_path();
      }
    }

    cout << working_dir;
    return true;
  }
};
