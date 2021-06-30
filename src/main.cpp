#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fmt/core.h>
#include <argparse/argparse.hpp>

#include "commit.hpp"
#include "change.hpp"
#include "minigit.hpp"
#include "repository.hpp"
#include "repositoryfinder.hpp"

using std::vector;
using argparse::ArgumentParser;

int main(int argc, char** argv) {
  ArgumentParser program("minigit", "0.1.0");

  program.add_argument<string>("command")
    .default_value<string>("")
    .help("Execute command");
  program.add_argument<string>("option1")
    .default_value<string>("")
    .help("First parameter of command");

  if (argc == 1) {
    string help = program.help().str();
    fmt::print(help);
    return 0;
  }

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    fmt::print("{}\n", err.what());
    return 1;
  }

  string command = program.get<string>("command");
  if (command.length() > 0) {
    if (command == "init") {
      string path = program.get<string>("option1");
      if (path.length() > 0) {
        Minigit::init(path);
        return 0;
      }
      Minigit::init();
      return 0;
    } else if (command == "hash") {
      string path = program.get<string>("option1");
      if (path.length() == 0) {
        fmt::print("fatal: a path is needed to hash the file.\n");
        return 1;
      }
      if (!fs::exists(path)) {
        fmt::print("fatal: cannot access '{}'.\n");
        return 1;
      }
      Minigit::hash(path);
      return 0;
    }

    try {
      RepositoryFinder::findRepository();
      Repository* repository = new Repository("main");
      repository->handleCommand(program, command);
      return 0;
    } catch (const std::exception& err) {
      fmt::print("{}\n", err.what());
      return 1;
    }

    fmt::print("minigit: '{}' is not a minigit command. See 'minigit --help'.\n", command);
    return 1;
  }

  string help = program.help().str();
  fmt::print(help);
  return 0;

  // User* user = new User("TestingUser", "testinguser@example.com");

  // Document* doc = new Document("file1.txt");
  // list<Change*> changes1; changes1.push_back(new Change(doc));
  // Commit* firstCommit = new Commit(changes1, "Initial commit", user);

  // Document* doc2 = new Document("hola2.txt");
  // Change* newChange = new Change(doc2); newChange->setDocPath("hola.txt");
  // list<Change*> changes2; changes2.push_back(newChange);
  // Commit* secondCommit = new Commit(changes2, "Another commit", user, firstCommit);

  // fmt::print("{}", secondCommit->getPatch());
  // fmt::print("{}", secondCommit->getHash());
}
