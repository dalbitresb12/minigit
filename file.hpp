#include <list>
#include <string>
using namespace std;

enum class FileType {
  Document,
  Folder
};

class File {
protected:
  string path;
  string name;
  list<File*> versions;
  File(string name, string path): name(name), path(path){}
public:
  bool compareName(string name) {
    return this->name == name;
  }

  virtual FileType getFileType() = 0;
};
