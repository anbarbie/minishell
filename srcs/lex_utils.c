/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:51:28 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 17:19:18 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_str(char *str, int start)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) - start + 1));
	while (str[start + i])
	{
		result[i] = str[start + i];
		i++;
	}
	result[i] = '\0';
	free (str);
	return (result);
}

int	is_special_char(char c)
{
	char	*set;
	int		i;

	set = " \"\'|<>";
	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*cpy_portion(char	*str, int start, int end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (end - start + 1));
	while (str[start] && start + i != end)
	{
		dest[i] = str[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim2(char *s1, char const *set)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (ft_isset(s1[i], set))
		i++;
	if (i == len)
	{
		free(s1);
		return (ft_strdup(""));
	}
	j = ft_strlen(s1) - 1;
	while (ft_isset(s1[j], set))
		j--;
	result = ft_substr(s1, i, j - i + 1);
	free(s1);
	return (result);
}
