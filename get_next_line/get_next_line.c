/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:52:03 by aessakhi          #+#    #+#             */
/*   Updated: 2021/12/13 18:29:42 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	create_line(char **str, char **line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_substr(*str, 0, i);
		tmp = ft_substr(*str, i + 1, ft_strlen(&(*str)[i + 1]));
		free(*str);
		*str = tmp;
		return (1);
	}
	else
	{
		*line = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = NULL;
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*str;
	int			ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, buf, 0))
		return (-1);
	if (!str)
		str = NULL;
	if (str == NULL)
		str = ft_calloc(sizeof(char *), 1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0 && isins(str, '\n') == 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin_gnl(str, buf);
		if (isins(str, '\n') == 0)
			ret = read(fd, buf, BUFFER_SIZE);
	}
	return (create_line(&str, line));
}
