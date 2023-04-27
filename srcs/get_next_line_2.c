/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:17:23 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 15:57:57 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*free_str(char	*str)
{
	free(str);
	str = NULL;
	return (str);
}

int	create_line_2(char **str, char **line, char *delimitor)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_substr(*str, 0, i);
		if (ft_strncmp_both(*line, delimitor) == 0)
		{
			(*str) = free_str(*str);
			return (0);
		}
		tmp = ft_substr(*str, i + 1, ft_strlen(&(*str)[i + 1]));
		free(*str);
		*str = tmp;
		return (1);
	}
	else
	{
		*line = ft_substr(*str, 0, ft_strlen(*str));
		(*str) = free_str(*str);
		return (0);
	}
}

int	get_next_line_2(int fd, char **line, char *delimitor)
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
	return (create_line_2(&str, line, delimitor));
}
