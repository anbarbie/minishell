/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:46:15 by aessakhi          #+#    #+#             */
/*   Updated: 2021/01/13 10:31:57 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dststr;
	const char	*srcstr;
	size_t		i;

	dststr = (char *)dst;
	srcstr = (const char *)src;
	if (dst == NULL && src == NULL)
		return (0);
	if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dststr[i] = srcstr[i];
		}
	}
	else
	{
		i = -1;
		while (++i < len)
			dststr[i] = srcstr[i];
	}
	return (dst);
}
