/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:06:09 by aessakhi          #+#    #+#             */
/*   Updated: 2021/05/20 15:12:06 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mallocsize(long int nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		size++;
	if (nb < 0)
	{
		nb = nb * -1;
		size++;
	}
	while (nb)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

static char	*ft_rev_int_tab(char *tab)
{
	int			i;
	char		swap;
	int			size;

	i = 0;
	size = ft_strlen(tab);
	size--;
	while (i < size)
	{
		swap = tab[i];
		tab[i] = tab[size];
		tab[size] = swap;
		i++;
		size--;
	}
	return (tab);
}

static char	*conv_nbr(long int nb, char *tab)
{
	int			signe;
	int			i;

	i = 0;
	signe = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		signe = 1;
	}
	if (nb == 0)
		tab[i++] = '0';
	while (nb)
	{
		tab[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (signe)
		tab[i++] = '-';
	tab[i++] = '\0';
	return (tab);
}

char	*ft_itoa(long int n)
{
	long int	nb;
	char		*result;
	int			size;
	int			i;

	nb = n;
	size = mallocsize(nb) + 1;
	result = malloc(sizeof(char) * size);
	if (!result)
		return (NULL);
	result = conv_nbr(nb, result);
	result = ft_rev_int_tab(result);
	i = ft_strlen(result);
	result[i] = '\0';
	return (result);
}
