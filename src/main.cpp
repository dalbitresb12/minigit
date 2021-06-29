#include <iostream>
#include "commit.hpp"
#include <fstream>
#include "change.hpp"
#include "repository.hpp"
using std::cout;

int main(int, char**) {
  //std::cout << "Hello, world!\n";
  //User* user = new User("FrowsyFrog", "frowsyfrog@gmail.com");
  //Commit com(user, "Prueba");
  //cout << com.getSha1() << endl << endl;

  //cout << com.getDiff();



  try {
    cout << Repository::findRepository();
  } catch(const std::runtime_error &err){
    cout << err.what() << "\n";
    return 1;
  }

  Document* doc = new Document("hola.txt");
  Change change(doc);
  //cout << "\n" << change.getObjPath();

  //cout << doc->getName();

  //delete user;
  
}
