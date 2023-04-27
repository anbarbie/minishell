/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:23:51 by antbarbi          #+#    #+#             */
/*   Updated: 2022/06/24 16:18:02 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	*dir;

	g_ret = 0;
	dir = getcwd((char *) NULL, 0);
	if (dir == NULL)
	{
		write(1, "error\n", 6);
		return (1);
	}
	else
	{
		ft_putendl_fd(dir, 1);
		free(dir);
		return (0);
	}
}
