/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:50:23 by antbarbi          #+#    #+#             */
/*   Updated: 2022/06/23 12:23:06 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	match(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (ft_strlen(str) != ft_strlen(cmd))
		return (0);
	while (cmd[i])
	{
		if (str[i] != cmd[i])
			return (0);
		i++;
	}
	return (1);
}

int	option_match(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **str)
{
	int	i;
	int	opt;

	opt = 0;
	g_ret = 0;
	i = 1;
	while (str[i] && option_match(str[i]))
	{
		i++;
		opt = 1;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!opt)
		ft_putchar_fd('\n', 1);
}
