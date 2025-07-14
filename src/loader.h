#ifndef LOADER_H
#define LOADER_H

char **load_text(const char *filename, int *line_count);
void free_text(char **text, int line_count);

#endif
