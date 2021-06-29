#pragma once
#include "dtl/dtl.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using dtl::Diff;
using dtl::elemInfo;
using dtl::uniHunk;

class DiffMeth {
public:
  static void strdiff(string stra, string strb) {
    typedef char elem;
    typedef string sequence;

    sequence A(stra);
    sequence B(strb);

    Diff<elem, sequence> d(A, B);
    d.compose();
    d.composeUnifiedHunks();

    cout << "editDistance: " << d.getEditDistance() << endl;
    vector<elem> lcs_v = d.getLcsVec();
    sequence lcs_s(lcs_v.begin(), lcs_v.end());
    cout << "LCS:" << lcs_s << endl;
    
    cout << "SES" << endl;
    d.printSES();

    //d.printUnifiedFormat();
  }

  static void filediff(fs::path fpath, fs::path spath) {
    unifiedDiff(fpath, spath);
  }

private:
  static void unifiedDiff(fs::path fp1, fs::path fp2) {
    typedef string elem; //string as Elem
    typedef vector<elem> sequence; // vector<elem> as Sequence

    ifstream fileA(fp1);
    ifstream fileB(fp2);

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
    diff.printUnifiedFormat(); // print a difference as Unified Format.

  }

  bool isFileExist(string& fs) {
    FILE* fp;
    if ((fp = fopen(fs.c_str(), "r")) == NULL) {
      return false;
    }
    fclose(fp);
    return true;
  }
};
