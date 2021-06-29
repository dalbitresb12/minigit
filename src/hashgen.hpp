#pragma once
#include <openssl/sha.h>
#include <string>
#include <sstream>

class HashGenerator {
public:
  static std::string hash(std::string ibuf) {
    unsigned char obuf[20];
    std::stringstream stream;
    SHA1((const unsigned char*)ibuf.c_str(), ibuf.length(), obuf);

    for (int i = 0; i < 20; ++i)
      stream << std::hex << (int)obuf[i];

    return stream.str();
  }
};
