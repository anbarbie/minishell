/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:23:49 by antbarbi          #+#    #+#             */
/*   Updated: 2022/06/24 16:21:01 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalnum_uscore(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int	check_export(char *export, int i)
{
	if (ft_isdigit(export[0]) || !(ft_isalnum_uscore(export[0])))
	{
		g_ret = 1;
		ft_putstr_exp(export);
		return (0);
	}
	while (export[i])
	{
		if (export[i] == '=')
			break ;
		if (!ft_isalnum_uscore(export[i]))
		{
			ft_putstr_exp(export);
			g_ret = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_putstr_decl(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	ft_putstr_fd("declare -x ", 1);
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		if (str[i] == '=' && !sign)
		{
			ft_putchar_fd('"', 1);
			sign++;
		}
		i++;
	}
	if (sign)
		ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
}

void	ft_sort_env(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] && env[i + 1])
	{
		if (strncmp(env[i], env[i + 1], 2) > 0)
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		ft_putstr_decl(env[i]);
		i++;
	}
}

void	ft_export(char **export, t_shell *shell)
{
	char	**cpy;
	int		i;

	i = 1;
	g_ret = 0;
	cpy = cpy_env(shell->env);
	if (!export[1])
		ft_sort_env(cpy);
	while (export[i])
	{
		if (check_export(export[i], 0))
			cpy = ft_export_arg(export[i], cpy);
		i++;
	}
	free_dbl_array(shell->env);
	shell->env = cpy;
}
