/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:31:33 by aessakhi          #+#    #+#             */
/*   Updated: 2021/01/09 12:41:02 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s_char;

	i = 0;
	s_char = (char *)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		s_char[i] = '\0';
		i++;
	}
}
