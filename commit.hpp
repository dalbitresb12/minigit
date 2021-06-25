#include <string>
#include <list>
using namespace std;

class Commit {
  string sha1;
  int timestap;
  list<File*> changes;
public:
  Commit() {}
  string getDiff() {

  }

};
