#pragma once

#include "hashtable.hpp"
#include "stash.hpp"

class StashManager {
  HashTable<Stash*> stashes;

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
