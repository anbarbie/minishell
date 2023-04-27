/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:42:09 by aessakhi          #+#    #+#             */
/*   Updated: 2021/05/20 15:14:09 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src,
							int c, size_t n)
{
	size_t					i;
	unsigned char			*dststr;
	unsigned char			*srcstr;
	unsigned char			cchar;

	dststr = (unsigned char *)dst;
	srcstr = (unsigned char *)src;
	cchar = c;
	i = 0;
	while (i < n)
	{
		dststr[i] = srcstr[i];
		i++;
		if (dststr[i - 1] == cchar)
			return (dststr + i);
	}
	return (NULL);
}
