#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dirent.h"

DIR *opendir(const char *name) {
    DIR *dir = (DIR *)malloc(sizeof(DIR));
    char search_path[MAX_PATH];

    snprintf(search_path, sizeof(search_path), "%s\\*", name);
    dir->hFind = FindFirstFile(search_path, &dir->find_data);

    if (dir->hFind == INVALID_HANDLE_VALUE) {
        free(dir);
        return NULL;
    }

    return dir;
}

struct dirent *readdir(DIR *dirp) {
    if (dirp->hFind == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    strncpy(dirp->current_entry.d_name, dirp->find_data.cFileName, MAX_PATH);

    if (dirp->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        dirp->current_entry.d_type = DT_DIR;
    } else {
        dirp->current_entry.d_type = DT_REG;
    }

    if (!FindNextFile(dirp->hFind, &dirp->find_data)) {
        FindClose(dirp->hFind);
        dirp->hFind = INVALID_HANDLE_VALUE;
    }

    return &dirp->current_entry;
}

int closedir(DIR *dirp) {
    if (dirp->hFind != INVALID_HANDLE_VALUE) {
        FindClose(dirp->hFind);
    }
    free(dirp);
    return 0;
}
