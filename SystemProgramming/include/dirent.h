#ifndef DIRENT_H
#define DIRENT_H

#include <windows.h>

#define DT_DIR  4
#define DT_REG  8

typedef struct dirent {
    char d_name[MAX_PATH]; // File or directory name
    unsigned char d_type;  // File type (DT_DIR or DT_REG)
} dirent;

typedef struct DIR {
    HANDLE hFind;
    WIN32_FIND_DATA find_data;
    struct dirent current_entry;
} DIR;

// Function to open a directory stream
DIR *opendir(const char *name);

// Function to read a directory entry
struct dirent *readdir(DIR *dirp);

// Function to close a directory stream
int closedir(DIR *dirp);

#endif // DIRENT_H
