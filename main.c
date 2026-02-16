#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    if (argc == 1)
    {
        // Leer desde stdin
        fd = 0;
        printf("Leyendo desde stdin (Ctrl+D para terminar):\n");
    }
    else
    {
        // Leer desde archivo
        fd = open(argv[1], O_RDONLY);
        if (fd < 0)
        {
            perror("Error al abrir el archivo");
            return (1);
        }
    }

    while ((line = get_next_line(fd)))
    {
        printf("LINEA -> %s", line);
        free(line);
    }

    if (argc > 1)
        close(fd);

    return (0);
}
