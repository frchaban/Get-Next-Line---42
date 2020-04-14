/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:34:40 by frchaban          #+#    #+#             */
/*   Updated: 2020/03/28 13:17:01 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_set_line(char const *str, char *line)
{
	unsigned int	i;
	unsigned int	j;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (line)
		free(line);
	if (!(line = (char *)malloc(sizeof(*line) * (i + 1))))
		return (NULL);
	line[i] = '\0';
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	return (line);
}

char *ft_read(int fd, char *str)
{
	int rd;
	char buffer[BUFFER_SIZE + 1];

	while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (rd == 0)
			return (0);
		buffer[rd] = '\0';
		if (str && str[0] != '\0')
			str = ft_strjoin(str, buffer);
		else
			str = ft_strjoin(ft_strdup(""), buffer);
		if (ft_strchr(str, '\n'))
			return (str);
	}
	if (rd == -1 || rd == 0)
		return (NULL);
	return (str);
}

int get_next_line(int fd, char **line)
{
	static char *str;

	if (str && ft_strchr(str, '\n'))
	{
		*line = ft_set_line(str, *line);
		str = ft_substr(str, ft_strlen(*line) + 1, ft_strlen(str));
		if (str && str[0] == '\0')
			free(str);
		return (1);
	}
	else if ((str = ft_read(fd, str)))
	{
		*line = ft_set_line(str, *line);
		str = ft_substr(str, ft_strlen(*line) + 1, ft_strlen(str));
		if (str && str[0] == '\0')
			free(str);
		return (1);
	}
	if (str == NULL)
		return (-1);
	return (0);
}

#include <fcntl.h>

int	main (int argc, char **argv)
{
	int fd;
	char *line;
	int countline;
	int	test;
	int i;

	i = 0;
	test = 0;

	countline = 1;
	line = NULL;
	if (argc == 1)
		fd = 0;
	else 
		fd = open(argv[1], O_RDONLY);
	while ((test = get_next_line(fd, &line)) > 0)
	{
		printf("line %d : %s\n", countline, line);
		countline++;
	}
	close(fd);
	return (0);
}
