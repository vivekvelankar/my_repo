#include <string>
#include <map>
#include <vector>

using std::vector;

class ReadFiles {
 public:
  ReadFiles(){};
  ~ReadFiles(){};

  // This routine goes over the directory in BFS manner to create
  // a list of all the files present in this subtree.
  std::vector<std::string> GetFileList(std::string top_dir_path);
};
