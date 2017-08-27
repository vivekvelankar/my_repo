#include <common.h>
#include <vector>

#include <read_files.h>

using std::string;
using std::vector;
using std::unordered_multimap;

int main() {
  string dir_path;
  ReadFiles* rf = new ReadFiles();

  unordered_multimap<string, string> file_map = rf->GetFileList(DIR_PATH);

  cout << "\n\nTesting\n";
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
    }
    cout << "Num matches " << file_map.count(key) << endl;
    for (int i = 0; i < file_map.count(key); i++, it++) {
      cout << "Looked up path is " << it->second << endl;
    }
  }
  return 0;
}
