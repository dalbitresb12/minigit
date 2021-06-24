#include <file.hpp>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class Document : public File {
  string ext;
public:
  Document(string path, string name) : File(path, name) {
    ext = getExt(path);
  }

  string getExt(string extPath) {
    fs::path path = fs::path(extPath);
    return path.extension().generic_u8string();
  }

  string hash() {
    //Falta agregar librería para hallar el hash
    return "";
  }
};

