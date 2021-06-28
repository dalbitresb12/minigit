#pragama once
#include "HashTables.hpp"
class StashManager {
  Hashtable<Stash*> stashes;

public:
  StashManager();
  ~StashManager();
  void list();
  void apply();
  void apply(string key);
  void pop();
  void pop(string key);
  void drop();
  void drop(string key);
};
