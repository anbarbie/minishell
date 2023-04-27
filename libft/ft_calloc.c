/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:28:57 by aessakhi          #+#    #+#             */
/*   Updated: 2021/05/20 15:11:02 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*block;

	block = malloc(count * size);
	if (!block)
		return (NULL);
	block = ft_memset(block, 0, count * size);
	return (block);
}
