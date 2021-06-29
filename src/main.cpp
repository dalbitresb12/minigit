#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

using std::string;
using std::cout;
using argparse::ArgumentParser;

int main(int argc, char** argv) {
  ArgumentParser program("minigit", "0.1.0");

  program.add_argument<string>("command")
    .default_value<string>("")
    .help("Execute command");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    cout << err.what() << "\n";
    return 1;
  }

  auto command = program.get<string>("command");
  if (command.length() > 0) {
    cout << "command passed: " << command << "\n";
    return 0;
  }

  cout << program;
  return 0;
}
