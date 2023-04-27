/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:49:19 by aessakhi          #+#    #+#             */
/*   Updated: 2021/05/24 15:02:39 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sepa(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*s2;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	end = ft_strlen(s1);
	while (sepa(s1[start], set) > 0)
		start++;
	while (sepa(s1[end - 1], set) > 0)
		end--;
	if (end - start <= 0)
		return (ft_substr(s1, 0, 0));
	else
		s2 = ft_substr(s1, start, end - start);
	return (s2);
}
