#include <stdio.h>
#include <time.h>
#include "logger.h"

void log_operation(const char *operation, const char *result) {
    FILE *log_file;
    time_t now;
    char time_str[100];

    log_file = fopen("operations.log", "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    time(&now);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

    fprintf(log_file, "[%s] %s: %s\n", time_str, operation, result);

    fclose(log_file);
}
