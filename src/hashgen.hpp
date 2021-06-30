#pragma once

#include <openssl/sha.h>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class HashGenerator {
public:
  static string hash(string ibuf) {
    unsigned char obuf[20];
    stringstream stream;
    SHA1((const unsigned char*)ibuf.c_str(), ibuf.length(), obuf);
    for (int i = 0; i < 20; ++i)
      stream << std::hex << (int)obuf[i];
    return stream.str();
  }
  static string hash(string* ibuf) {
    unsigned char obuf[20];
    stringstream stream;
    SHA1((const unsigned char*)ibuf->c_str(), ibuf->length(), obuf);
    for (int i = 0; i < 20; ++i)
      stream << std::hex << (int)obuf[i];
    return stream.str();
  }
};
