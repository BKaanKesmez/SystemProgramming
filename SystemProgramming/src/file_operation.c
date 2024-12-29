#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "file_operations.h"


// Define constants for compatibility
#define O_RDONLY 0x0         // Open for reading only
#define O_WRONLY 0x1         // Open for writing only
#define O_CREAT  0x100       // Create file if it doesn't exist

// Define macros to map original function names to Windows API calls
#define open(path, flags) CreateFile(path, (flags & O_WRONLY ? GENERIC_WRITE : GENERIC_READ), 0, NULL, (flags & O_CREAT ? CREATE_ALWAYS : OPEN_EXISTING), FILE_ATTRIBUTE_NORMAL, NULL)
#define read(fd, buffer, size) ReadFile(fd, buffer, size, &bytes_read, NULL)
#define write(fd, buffer, size) WriteFile(fd, buffer, size, &bytes_written, NULL)
#define close(fd) CloseHandle(fd)
#define unlink(path) DeleteFile(path)
#define rmdir(path) RemoveDirectory(path)


void create_file(const char *path) {
    HANDLE file_handle;

    // Attempt to create the file (O_CREAT flag will create the file if it doesn't exist)
    file_handle = open(path, O_WRONLY | O_CREAT);
    if (file_handle == INVALID_HANDLE_VALUE) {
        perror("Failed to create file");
        return;
    }

    // Close the file handle since the file has been successfully created
    close(file_handle);
    printf("File created successfully.\n");
}
void move_file(const char *source, const char *destination) {
    if (rename(source, destination) == 0) {
        printf("File moved successfully.\n");
    } else {
        perror("Error moving file");
    }
}

// Function to copy a file
void copy_file(const char *source, const char *destination) {
    HANDLE src_fd, dest_fd;
    char buffer[1024];
    DWORD bytes_read, bytes_written;

    // Open the source file
    src_fd = open(source, O_RDONLY);
    if (src_fd == INVALID_HANDLE_VALUE) {
        perror("Failed to open source file");
        return;
    }

    // Create the destination file
    dest_fd = open(destination, O_WRONLY | O_CREAT);
    if (dest_fd == INVALID_HANDLE_VALUE) {
        perror("Failed to open destination file");
        close(src_fd);
        return;
    }

    // Read from source and write to destination
    while (read(src_fd, buffer, sizeof(buffer)) && bytes_read > 0) {
        if (!write(dest_fd, buffer, bytes_read) || bytes_written != bytes_read) {
            perror("Write error");
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    close(src_fd);
    close(dest_fd);
    printf("File copied successfully.\n");
}

// Function to remove a file or directory
void remove_file_or_dir(const char *path) {
    // Attempt to delete a file
    if (unlink(path)) {
        printf("File removed successfully.\n");
    }
    // If not a file, attempt to delete a directory
    else if (rmdir(path)) {
        printf("Directory removed successfully.\n");
    }
    // If both failed, print an error
    else {
        perror("Error removing file or directory");
    }
}
