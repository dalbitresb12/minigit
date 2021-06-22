#include <list>
#include <string>
using namespace std;

class File abstract {
  string path;
  string name;
  list<File*> versions;
public:
  string getName() {
    return name;
  }

  virtual bool contains(string name) {
    return this.name.compare(name);
  }
};
