/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:48:56 by aessakhi          #+#    #+#             */
/*   Updated: 2021/01/25 11:25:20 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			*sstr;
	size_t					i;

	sstr = (void *)s;
	i = 0;
	while (i < n)
	{
		if (sstr[i] == (unsigned char)c)
			return ((void *)(sstr + i));
		i++;
	}
	return (NULL);
}
