/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykhan-i <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:15:31 by aykhan-i          #+#    #+#             */
/*   Updated: 2026/02/12 19:32:53 by aykhan-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*  
Esta función se encarga de leer el file descriptor. He tenido de dividir en dos 
funciones ya que me causaba fugas de memoria(LEAK).
Comienza a leer byte por byte (leer letra por letra) hasta el tamaño del buffer (n).
Hacemos dos verificaciones de seguridad: la primera es el caso de negativos (-) 
que me devuelva -1 si los bytes leidos son cero o un numero negativo, 
y la segunda es si los bytes a leer son cero, es decir, no hay nada que leer, 
pues directamente se detiene. Si todo ha salido bien y ha pasado las verificaciones 
de seguridad, pasamos a añadir el carácter nulo un vez copiado en el buffer.
Ahora, para poder evitar fugas de memoria (LEAK), lo que haremos es guardar el
contenido del stack en una variable temporal. Una vez hecho eso, pasamos a utilizar
la función ft_strjoin, y con el contenido que está guardado en la variable temporal
y la memoria, pasamos a concatenar (unir) las cadenas. Una vez hecho eso, liberamos
la variable temporal y liberamos el bloque de memoria, y devolvemos la variable 
result ya que es la que almacena el resulado (contenido leido).
*/

static int	fill_buffer(int fd, char **stash, char	*buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(*stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = *stash;
		*stash = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	return (0);
}

static int	read_line(int fd, char **stash)
{
	char	*buffer;
	int		result;

	if (*stash == NULL)
		*stash = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	result = fill_buffer(fd, stash, buffer);
	free(buffer);
	return (result);
}

/*
En esta función limpiamos el stash. Si el stash no existe, devolvemos un NULL.  
Mientras el stash exista y no estemos en un salto de línea, que continúe iterando. 
Hacemos una verificación donde si el stash está vacío, liberamos la memoria que 
previamente reservamos y devolvemos un NULL.  
Si todo está bien, hacemos una copia del nuevo stash y devuelve la dirección de 
memoria del puntero al stash, avanzando el puntero a la siguiente posición (i + 1). 
Liberamos el stash original y devolvemos el nuevo stash.
*/

static char	*clear_stash(char *stash)
{
	char	*new_stash;
	size_t	i;

	if (stash == NULL)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(&stash[i + 1]);
	free(stash);
	return (new_stash);
}

/*
Con esta función extraemos la línea del stash y la guardamos para ir acumulando.  
Si el stash no existe, devolvemos NULL. Mientras el stash exista y no encontremos 
un salto de línea, seguimos iterando.  
Si el stash encuentra un salto de línea, incluimos ese salto paramos hay.
Reservamos un byte extra para el '\0'.  
Si la nueva línea no existe, devolvemos NULL y paramos.  
Luego, copiamos byte por byte del stash a la nueva línea hasta completar la línea 
extraída.  
Finalmente, agregamos el carácter nulo '\0' al final y devolvemos la nueva línea.
*/

static char	*extract_line(char *stash)
{
	int		i;
	int		j;
	char	*new_line;

	if (stash == NULL)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	new_line = malloc(i + 1);
	if (!new_line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_line[j] = stash[j];
		j++;
	}
	new_line[i] = '\0';
	return (new_line);
}

/*
Esta es la función principal de get_next_line. Primero se hace una verificación 
de seguridad: se asegura que el fd sea válido, que BUFFER_SIZE sea mayor que 0 y 
que el descriptor sea legible; si falla alguna condición, se libera la memoria 
de 'stash' y se retorna NULL.  

Luego se llama a read_line para leer del fd; si ocurre un error (devuelve -1), 
se libera 'stash' y se retorna NULL.  

Después se comprueba que 'stash' exista y no esté vacío; si está vacío, se libera 
y se retorna NULL.  

Si todo está correcto, se extrae la línea de 'stash' con extract_line, 
se limpia el 'stash' con clear_stash, y se retorna la línea leída.
*/

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (read_line(fd, &stash) == -1)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = clear_stash(stash);
	return (line);
}
