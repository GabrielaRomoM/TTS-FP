#ifndef LOADER_H
#define LOADER_H

// Carga del contenido del archivo en memoria
char **load_text(const char *filename, int *line_count);
// Libera el contenido cargado
void free_text(char **text, int line_count);

#endif
