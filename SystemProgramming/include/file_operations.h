#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Function to copy a file from source to destination
void copy_file(const char *source, const char *destination);

// Function to remove a file or directory
void remove_file_or_dir(const char *path);

void create_file(const char *path);

void move_file(const char *source, const char *destination);

#endif // FILE_OPERATIONS_H
