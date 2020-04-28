/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:34:40 by frchaban          #+#    #+#             */
/*   Updated: 2020/04/28 18:22:13 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_set_line(char const *str, char *line)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
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

char	*ft_read(int fd, char *str, int *flag)
{
	int		rd;
	char	buffer[BUFFER_SIZE + 1];

	while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rd] = '\0';
		if (str && str[0] != '\0')
			str = ft_strjoin(str, buffer);
		else
			str = ft_strjoin(ft_strdup(""), buffer);
		if (ft_strchr(str, '\n'))
			return (str);
	}
    if (rd == 0)
    {
        *flag = 1;
        return (str);
    }
	if (rd == -1)
		return (NULL);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char *str;
    int         flag;

    if (fd < 0 || line == NULL)
        return (-1);
	if (str && str[0] != '\0' && ft_strchr(str, '\n'))
	{
		*line = ft_set_line(str, *line);
		str = ft_substr(str, ft_strlen(*line) + 1, ft_strlen(str));
		if (str && str[0] == '\0')
        {
			free(str);
            str = NULL;
        }
		return (1);
	}
	else if ((str = ft_read(fd, str, &flag)))
	{
		*line = ft_set_line(str, *line);
		str = ft_substr(str, ft_strlen(*line) + 1, ft_strlen(str));
		if (str && str[0] == '\0')
        {
			free(str);
            str = NULL;
        }
        if (flag == 1)
            return (0);
		return (1);
	}
    if (fd == 0 && flag == 1)
        return (0);
    if (flag == 1 && str)
            return (0);
	if (str == NULL)
		return (-1);
	return (0);
}
