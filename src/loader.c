#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"

#define MAX_LINES 1000
#define LINE_LEN 256

char **load_text(const char *filename, int *line_count) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    char **lines = malloc(MAX_LINES * sizeof(char *));
    char buffer[LINE_LEN];
    *line_count = 0;

    while (fgets(buffer, LINE_LEN, file) && *line_count < MAX_LINES) {
        lines[*line_count] = strdup(buffer);
        (*line_count)++;
    }

    fclose(file);
    return lines;
}

void free_text(char **text, int line_count) {
    for (int i = 0; i < line_count; ++i)
        free(text[i]);
    free(text);
}
