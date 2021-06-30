#pragma once

#include <dtl/dtl.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using std::pair;
using std::string;
using std::vector;
using std::stringstream;
using std::fstream;
using std::ios;

class DiffUtils {
public:
  static string unified(fs::path previous, fs::path current) {
    fstream fileA(previous, ios::in | ios::binary);
    fstream fileB(current, ios::in | ios::binary);

    string buf;
    vector<string> ALines, BLines;

    while (getline(fileA, buf)) {
      ALines.push_back(buf);
    }
    while (getline(fileB, buf)) {
      BLines.push_back(buf);
    }

    dtl::Diff<string> diff(ALines, BLines);

    diff.onHuge(); // Optimize the calculation of difference
    diff.compose(); // Construct an edit distance and LCS and SES
    diff.composeUnifiedHunks(); // Construct a difference as Unified Format with SES.

    stringstream diffstream;
    diff.printUnifiedFormat(diffstream); // Save difference as Unified Format.
    return diffstream.str();
  }
};
