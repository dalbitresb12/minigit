#include <iostream>
#include <fstream>
#include <string>
#include <argparse/argparse.hpp>

#include "commit.hpp"
#include "change.hpp"
#include "repository.hpp"

using std::cout;
using argparse::ArgumentParser;

int main(int argc, char** argv) {
  try {
    cout << Repository::findRepository() << "\n\n";
  } catch (const std::runtime_error& err) {
    cout << err.what() << "\n";
    return 1;
  }

  // ArgumentParser program("minigit", "0.1.0");

  // program.add_argument<string>("command")
  //   .default_value<string>("")
  //   .help("Execute command");

  // try {
  //   program.parse_args(argc, argv);
  // } catch (const std::runtime_error& err) {
  //   cout << err.what() << "\n";
  //   return 1;
  // }

  // auto command = program.get<string>("command");
  // if (command.length() > 0) {
  //   cout << "command passed: " << command << "\n";
  //   return 0;
  // }

  // cout << program;
  // return 0;

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
