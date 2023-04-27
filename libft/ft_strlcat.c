/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:13:50 by aessakhi          #+#    #+#             */
/*   Updated: 2021/01/09 12:47:21 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	result;

	result = ft_strlen(dst) + ft_strlen(src);
	i = 0;
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	j = ft_strlen(dst);
	while (j + i < dstsize - 1 && src[i])
	{
		dst[j + i] = src[i];
		i++;
	}
	if (dstsize < j)
		return (dstsize + ft_strlen(src));
	if (j < dstsize)
		dst[j + i] = '\0';
	return (result);
}
