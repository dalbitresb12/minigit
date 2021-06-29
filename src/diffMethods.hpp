#pragma once
#include "dtl/dtl.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "commit.hpp"

using std::pair;
using std::string;
using std::stringstream;
using std::to_string;
using dtl::Diff;
using dtl::elemInfo;
using dtl::uniHunk;

class DiffMeth {
public:
  static string unifiedDiff(fs::path fpath, fs::path spath) {
    typedef string elem; //string as Elem
    typedef vector<elem> sequence; // vector<elem> as Sequence
    typedef pair<elem, elemInfo> sesElem;

    ifstream fileA(fpath);
    ifstream fileB(spath);

    elem buf;
    sequence ALines, BLines;

    while (getline(fileA, buf)) {
      ALines.push_back(buf);
    }
    while (getline(fileB, buf)) {
      BLines.push_back(buf);
    }

    Diff<elem> diff(ALines, BLines);

    diff.onHuge(); // Optimize the calculation of difference
    //diff.onUnserious(); // All difference is not Unserious difference when is ON
    diff.compose(); // Construct an edit distance and LCS and SES

    diff.composeUnifiedHunks(); // construct a difference as Unified Format with SES.

    stringstream diffstream;
    diff.printUnifiedFormat(diffstream); // print a difference as Unified Format.
    return diffstream.str();
  }

private:


};
