#include <string>
#include <unordered_map>

class ReadFiles {
 public:
  ReadFiles(){};
  ~ReadFiles(){};

  // This routine goes over the directory in BFS manner to create
  // a list of all the files present in this subtree.
  std::unordered_multimap<std::string, std::string> GetFileList(std::string top_dir_path);

  std::string get_file_key(std::string filepath);

  void dump_map(const std::unordered_multimap<std::string, std::string>& file_map);
};
