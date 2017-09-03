#include <map>
#include <queue>
#include <openssl/md5.h>
#include <sstream> 

#include <common.h>
#include <read_files.h>

using std::fstream;
using std::string;
using std::vector;
using std::queue;
using std::unordered_multimap;

unordered_multimap<string, string> ReadFiles::GetFileList(string path) {
  unordered_multimap<string, string> file_map;

  cout << "Directory to create maps from: " << path << endl;
  
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
      if (stat( filepath.c_str(), &filestat)) continue;
      if (S_ISDIR(filestat.st_mode)) {
        cout << "Parsing Directory " << filepath << endl;
        dir_list.push(filepath);
      } else {
        cout << "Adding path " << filepath << endl;
        string key = get_file_key(filepath);
        file_map.insert(make_pair(key, filepath));
      }
    }
    closedir(dp);
    dir_list.pop();
  }
  return file_map;
}

string ReadFiles::get_file_key(string filepath) {
  fstream fin;
  struct stat filestat;
  stat(filepath.c_str(), &filestat);
  fin.open(filepath.c_str(), std::ios::in | std::ios::binary);
  if (!fin) {
    cout << "\n***Unable to open " << filepath << "***\n" << endl;
    exit(1);
  }

  int hash_len  = FILE_HASH_LEN;
  if (filestat.st_size < FILE_HASH_LEN) {
    cout << "Resetting hash len" << endl;
    hash_len=filestat.st_size;
  }
  char key[hash_len];
  fin.read(key, hash_len);
  if (!fin) std::cout << "error: only " << fin.gcount() << " could be read";
  string md5;
  {
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)key, hash_len, result);

    std::stringstream ss;
    for(int i=0; i <MD5_DIGEST_LENGTH; i++) {
      ss << std::hex << result[i];
    }
    md5 = ss.str();
  }

  fin.close();
  cout << "### Key ###\n\tfile_size "
       << filestat.st_size <<  " \n\tkey " << md5 << endl;
  return md5;
}

void ReadFiles::dump_map(const std::unordered_multimap<std::string, std::string>& file_map) {
  fstream map_file(MAP_FILE_NAME, std::ios::out|std::ios::binary);

  if (map_file.is_open()) {
    string prev_key;
    for (auto pair : file_map) {
      string cur_key = pair.first;
      if (!prev_key.empty() && prev_key == cur_key) {
        map_file << "DUPLICATE " << pair.second << endl;
      } else {
        map_file << pair.second << endl;
        prev_key = pair.first;
      }
      //map_file << pair.second << endl;
    }
  }
}
