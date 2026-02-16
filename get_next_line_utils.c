/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykhan-i <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 22:06:32 by aykhan-i          #+#    #+#             */
/*   Updated: 2026/02/08 22:59:15 by aykhan-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	caracter;

	caracter = (char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == caracter)
			return ((char *)&str[i]);
		i++;
	}
	if (caracter == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	int		i;
	int		j;
	char	*memoria;

	if (!str1 && !str2)
		return (NULL);
	memoria = (char *)malloc((ft_strlen(str1) + ft_strlen(str2) + 1)
			* sizeof(char));
	if (!memoria)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		memoria[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		memoria[i + j] = str2[j];
		j++;
	}
	memoria[i + j] = '\0';
	return (memoria);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*revervar_memoria;

	if (!str)
		return (NULL);
	i = 0;
	revervar_memoria = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!revervar_memoria)
		return (NULL);
	while (str[i] != '\0')
	{
		revervar_memoria[i] = str[i];
		i++;
	}
	revervar_memoria[i] = '\0';
	return (revervar_memoria);
}
