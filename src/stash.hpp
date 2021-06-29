#pragma once

#include <string>
#include <list>

#include "file.hpp"

using std::string;
using std::list;

class Stash {
  string branch;
  list<File*> changes;

public:
  Stash();
  ~Stash();
  string getDiff();
};
