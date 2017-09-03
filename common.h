#include <string>
#include <cerrno>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using std::cin;
using std::cout;
using std::flush;
using std::endl;

const long int FILE_HASH_LEN = 1000;
const std::string MAP_FILE_NAME = "map_file.txt";
