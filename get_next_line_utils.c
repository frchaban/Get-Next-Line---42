/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:36:48 by frchaban          #+#    #+#             */
/*   Updated: 2020/03/28 13:17:13 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*tronc;

	if (!s)
		return (NULL);
	if (!(tronc = (char *)malloc(sizeof(*tronc) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		tronc[i] = s[start + i];
		i++;
	}
	free(s);
	return (tronc);
}

int	ft_strchr(const char *s, char c)
{
	unsigned int i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*s;

	if (!s1 || !s2)
		return (NULL);
	if (!(s = (char *)malloc(sizeof(*s) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	free (s1);
	return (s);
}

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(*src) * (ft_strlen(src) + 1));
	if (ptr == NULL)
		return (0);
	while (i < (int)ft_strlen(src))
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}