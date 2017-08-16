#include <constants.h>
#include <read_files.h>
#include <vector>

int main() {
  string dir_path;
  ReadFiles* rf = new ReadFiles();

  vector<string> list = rf->GetFileList(DIR_PATH);
  return 0;
}
