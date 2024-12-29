#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"
#include "dirent.h"

int main() {
    char command[256];
    char path1[256], path2[256],search_term[256];

    printf("Welcome to the Terminal File Manager\n");

    while (1) {
        printf("> ");
        fgets(command, 256, stdin);
        command[strcspn(command, "\n")] = '\0';  // Remove newline character

        if (strncmp(command, "slist", 5) == 0) {
            sscanf(command, "slist %s", path1);
            list_directory(path1);
        } else if (strncmp(command, "scopy", 5) == 0) {
            sscanf(command, "scopy %s %s", path1, path2);
            copy_file(path1, path2);
        } else if (strncmp(command, "sremove", 7) == 0) {
            sscanf(command, "sremove %s", path1);
            remove_file_or_dir(path1);
        } else if (strncmp(command, "screate", 7) == 0) {
            sscanf(command, "screate %s", path1);
            create_file(path1);  // Call the create_file function
        } else if (strncmp(command, "smove", 5) == 0) {
            sscanf(command, "smove %s %s", path1, path2);
            move_file(path1, path2);
        }
          else if (strncmp(command, "sperm", 5) == 0) {
            sscanf(command, "sperm %s %s", path1, path2);
            change_permissions(path1, path2);
        }else if (strncmp(command, "ssearch", 7) == 0) {  // Added file search functionality
            sscanf(command, "ssearch %s %s", path1, search_term);
            search_files(path1, search_term); 
        }else if (strncmp(command, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}
