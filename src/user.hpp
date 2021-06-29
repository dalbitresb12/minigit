#pragma once
#include <string>

using std::string;

class User {
  string name;
  string mail;
public:
  User(string n, string m): name(n), mail(m){}

  string getName() {
    return name;
  }

  string getMail() {
    return mail;
  }

  void setName(string n) {
    name = n;
  }

  void setMail(string m) {
    mail = m;
  }

};
