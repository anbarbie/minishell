/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:35:22 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/21 15:59:26 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atol(const char *str)
{
	long	atoi;
	int		n;

	atoi = 0;
	n = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			n = n * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		atoi = (long)(atoi * 10) + (long)(*str - 48);
		str++;
	}
	return (atoi * n);
}

int	str_is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_putexit_alpha(void)
{
	g_ret = 2;
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
}

void	ft_exit_single_cmd(t_shell *shell, t_cmd *cmd)
{
	ft_putstr_fd("exit\n", shell->std_out);
	if (env_size(cmd->cmd_array) > 2)
	{
		if (!str_is_num(cmd->cmd_array[1]))
		{
			ft_putexit_alpha();
			free_everything(shell);
			exit(g_ret);
		}
		g_ret = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	if (cmd->cmd_array[1])
	{
		if (!str_is_num(cmd->cmd_array[1]))
			ft_putexit_alpha();
		else
			g_ret = ft_atol(cmd->cmd_array[1]);
	}
	free_everything(shell);
	exit(g_ret);
}

void	ft_exit_pipe(t_cmd *cmd)
{
	if (env_size(cmd->cmd_array) > 2)
	{
		if (!str_is_num(cmd->cmd_array[1]))
		{
			ft_putexit_alpha();
			return ;
		}
		g_ret = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	if (cmd->cmd_array[1])
	{
		if (!str_is_num(cmd->cmd_array[1]))
			ft_putexit_alpha();
		else
			g_ret = ft_atol(cmd->cmd_array[1]);
	}
}
