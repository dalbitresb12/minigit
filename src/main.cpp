#include <iostream>
#include "commit.hpp"
#include <fstream>
#include "change.hpp"

int main(int, char**) {
  //std::cout << "Hello, world!\n";
  //User* user = new User("FrowsyFrog", "frowsyfrog@gmail.com");
  //Commit com(user, "Prueba");
  //cout << com.getSha1() << endl << endl;

  //cout << com.getDiff();

  Document* doc = new Document("hola.txt");
  Change change(doc);


  
  //cout << doc->getName();
  //Change()

  //delete user;
  
}
