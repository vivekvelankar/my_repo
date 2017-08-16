#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <cerrno>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <read_files.h>

using std::fstream;
using std::string;
using std::cin;
using std::cout;
using std::flush;
using std::endl;
using std::vector;
using std::queue;

vector<string> ReadFiles::GetFileList(string path) {
  // TODO(vivek) change this to map (sha1 of img to filename).
  std::vector<std::string> file_list;
  cout << "dir to create maps from: " << path << endl;
  
  queue<string> dir_list;
  dir_list.push(path);

  while(!dir_list.empty()) {
    string dir_path = dir_list.front();
    cout << "Listing files for " << dir_path << endl;
    DIR* dp = opendir(dir_path.c_str());
    if (dp == NULL) {
      cout << "Error(" << errno << ") opening " << dir_path << endl;
      exit(1);
    }

    struct dirent* dirp;
    while ((dirp = readdir(dp))) {
      if (dirp->d_name[0] == '.') continue;

      // Skip the invalid files.
      struct stat filestat;
      string filepath = dir_path + "/" + dirp->d_name;
      if (stat( filepath.c_str(), &filestat )) continue;
      if (S_ISDIR(filestat.st_mode)) {
        cout << "Adding dir " << filepath << endl;
        dir_list.push(filepath);
      } else {
        cout << "path " << filepath << endl;
        fstream fin;
        fin.open(filepath.c_str(), std::ios::binary);
        char key[std::min((long int)100, filestat.st_size)];
        fin >> key;
        cout << "size " << filestat.st_size << " key " << sizeof(key) << endl;
        cout << "file content   " << key << endl;
        file_list.push_back(filepath);
      }
    }
    closedir(dp);
    dir_list.pop();
  }
  return file_list;
}
