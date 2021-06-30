#pragma once

#include <string>

using std::string;

class User {
  string name;
  string email;
public:
  User(string name, string email)
    : name(name), email(email) {}

  string getName() {
    return name;
  }

  string getEmail() {
    return email;
  }
};
