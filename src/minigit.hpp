#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

class Minigit {
  map<string, string> configmap;

public:
  Minigit();
  ~Minigit();
  string config(string key);
  void config(string key, string value);
  void init();
  void init(string path);
  void clone(string path);
};
