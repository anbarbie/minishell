/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:48:33 by aessakhi          #+#    #+#             */
/*   Updated: 2021/05/24 14:59:16 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(char const *s, char c)
{
	int	i;
	int	word;
	int	word_count;

	i = 0;
	word = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] == c)
			word = 0;
		if (word == 0 && (s[i] != c))
		{
			word = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

static int	length(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i])
	{
		if (s[i] != c)
			size++;
		i++;
	}
	return (size);
}

static char	**free_arrays(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**spl(char const *s, char c, char **tab, int x)
{
	int	i;
	int	y;

	i = -1;
	y = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			if (y == 0)
			{
				tab[x] = malloc(sizeof(char) * length(s, c, i) + 1);
				if (!(tab[x]))
					free_arrays(tab);
			}
			tab[x][y] = s[i];
			tab[x][++y] = '\0';
		}
		if (s[i] == c && y > 0)
		{
			x++;
			y = 0;
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		x;

	x = 0;
	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * ((words(s, c) + 1)));
	if (!tab)
		return (NULL);
	tab = spl(s, c, tab, x);
	tab[(words(s, c))] = 0;
	return (tab);
}
