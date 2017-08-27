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

const std::string DIR_PATH="/fat32/test_images";

const long int FILE_HASH_LEN = 1000;
