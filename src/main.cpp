#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

using std::string;
using std::cout;

int main(int argc, char** argv) {
  argparse::ArgumentParser program("minigit", "0.1.0");

  program.add_argument("command")
    .action([](const string& value) { return value; })
    .help("Execute command");
  program.add_argument("-v", "--version")
    .default_value(false)
    .implicit_value(true)
    .help("Get program version");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    cout << err.what() << "\n";
    cout << "parsing error\n";
    return 1;
  }

  if (program.present("--version")) {
    cout << "v0.1.0\n";
    return 0;
  }

  if (program["command"] == true) {
    auto input = program.get<string>("command");
    cout << "command passed: " << input << "\n";
    return 0;
  }

  cout << "usage: " << argv[0] << " init\n";
  return 0;
}
