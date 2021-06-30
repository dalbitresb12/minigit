#include <iostream>
#include <fstream>

#include "commit.hpp"
#include "change.hpp"
#include "repository.hpp"

using std::cout;

int main(int, char**) {
  try {
    cout << Repository::findRepository() << "\n\n";
  } catch (const std::runtime_error& err) {
    cout << err.what() << "\n";
    return 1;
  }

  User* user = new User("FrowsyFrog", "frowsyfrog@gmail.com");

  Document* doc = new Document("hola.txt");
  list<Change*> changes1; changes1.push_back(new Change(doc));
  Commit* fCommit = new Commit(changes1, "Primer commit", user);

  Document* doc2 = new Document("hola2.txt");
  Change* newChange = new Change(doc2); newChange->setDocPath("hola.txt");
  list<Change*> changes2; changes2.push_back(newChange);
  Commit* sCommit = new Commit(changes2, "Segundo commit", user, fCommit);

  cout << sCommit->getPatch();
  cout << sCommit->getHash();
  return 0;
}
