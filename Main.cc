#include <common.h>
#include <vector>

#include <read_files.h>

using std::string;
using std::vector;
using std::unordered_multimap;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "****Error: Specify the top dir to index.";
    exit(1);
  }

  string dir_path;
  ReadFiles* rf = new ReadFiles();

  unordered_multimap<string, string> file_map = rf->GetFileList(argv[1]);
  cout << "\n\nTesting\n";
  
  rf->dump_map(file_map);
  vector<string> file_test;
  file_test.push_back("/fat32/git_ws/my_repo/build/Makefile");
  file_test.push_back("/fat32/git_ws/my_repo/build/CTestTestfile.cmake");
  file_test.push_back("/fat32/test_images/1/a/kapoor-and-sons-3a.jpg");
  
  for (auto s : file_test) {
    cout << "\n\nLooking up " << s << endl;
    string key = rf->get_file_key(s);
    auto it = file_map.find(key);
    if (it == file_map.end()){
      cout << "*** Unable to find " << s << "***." << endl;
      continue;
    }
    auto match_range = file_map.equal_range(key);
    for(auto it = match_range.first; it != match_range.second;it++) {
      cout << "Found image at " << it->second << endl;
    }
  }
  return 0;
}

