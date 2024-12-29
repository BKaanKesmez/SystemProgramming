#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <direct.h>
#include "directory_ops.h"

// Function to search for a string in a file's content
int search_in_file(const char *filename, const char *search_term) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_term)) {
            fclose(file);
            return 1;  // Found the search term in the file content
        }
    }

    fclose(file);
    return 0;  // Search term not found in the file content
}

// Function to search for a string in filenames within a directory
void search_files(const char *directory, const char *search_term) {
    DIR *dir = opendir(directory);
    if (!dir) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    int found = 0;

    // Iterate through the files in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Check if the filename contains the search term
        if (strstr(entry->d_name, search_term)) {
            printf("Found in filename: %s\n", entry->d_name);
            found = 1;
        }

        // If it's a file, search inside the file content
        if (entry->d_type == DT_REG) {  // Regular file
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);
            if (search_in_file(filepath, search_term)) {
                printf("Found in file content: %s\n", entry->d_name);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matches found for '%s'.\n", search_term);
    }

    closedir(dir);
}

void create_directory(const char *path) {

    if (_mkdir(path) == -1) {
        perror("Failed to create directory");
    } else {
        printf("Directory created successfully: %s\n", path);
    }

}
void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[512];

    dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        stat(full_path, &file_stat);
        printf("Name: %s\tType: %s\tSize: %ld bytes\n",
               entry->d_name,
               S_ISDIR(file_stat.st_mode) ? "Directory" : "File",
               file_stat.st_size);
    }

    closedir(dir);
}

