/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:51:07 by aessakhi          #+#    #+#             */
/*   Updated: 2021/01/12 12:41:08 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1str;
	char	*s2str;
	size_t	i;

	s1str = (char *)s1;
	s2str = (char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && s1str[i] == s2str[i])
		i++;
	return ((unsigned char)(s1str[i]) - (unsigned char)(s2str[i]));
}
