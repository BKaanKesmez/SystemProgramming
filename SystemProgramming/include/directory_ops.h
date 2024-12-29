#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

// Function to list the contents of a directory
void list_directory(const char *path);

// Function to create a new directory
void create_directory(const char *path);

void search_files(const char *directory, const char *search_term);

// Function to search for a term in a single file's content
int search_in_file(const char *filename, const char *search_term);

#endif // DIRECTORY_OPS_H
