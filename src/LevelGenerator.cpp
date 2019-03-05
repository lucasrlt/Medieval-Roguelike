#include <string>
#include <dirent.h>
#include <cstdio>
#include <string>
#include <iostream>
#include "LevelGenerator.h"

using namespace std;

LevelGenerator::LevelGenerator() {

}

void LevelGenerator::fetchRooms(char* dir) {
    vector<string> files;

    DIR *dirp;
    struct dirent *dp;

    /* Open the current directory */
    dirp = opendir(dir);
    assert( dirp);

    while ((dp = readdir(dirp)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            files.push_back(dp->d_name);
        }
    }

    closedir(dirp);


    for(auto it = files.begin(); it != files.end(); ++it) {
        cout << *it << endl;
    }


}