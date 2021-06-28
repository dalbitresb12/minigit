#pragma once
class Stash {
  string branch;
  list<File*> changes;
public:
  Stash();
  ~Stash();
  string getDiff();

};
