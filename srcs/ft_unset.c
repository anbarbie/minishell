/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:23:53 by antbarbi          #+#    #+#             */
/*   Updated: 2022/06/24 16:03:25 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_exp(char *str)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid indentifier\n", 2);
}

void	ft_putstr_uns(char *str)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid indentifier\n", 2);
}

int	check_unset(char *export, int i, int cpt, int forb)
{
	if (ft_isdigit(export[0]) || export[0] == '=')
	{
		g_ret = 1;
		ft_putstr_uns(export);
		return (0);
	}
	while (export[i] && export[i] != ' ')
	{
		if (export[0] != '=' && export[i] == '=')
		{
			cpt++;
			break ;
		}
		else if (!ft_isalnum_uscore(export[i]))
		{
			g_ret = 1;
			forb++;
		}
		i++;
	}
	if (cpt == 0 && forb == 0)
		return (1);
	ft_putstr_uns(export);
	return (0);
}

char	**ft_del_env(char **env, int id)
{
	int		i;
	int		j;
	int		size;
	char	**cpy;

	i = 0;
	j = 0;
	size = env_size(env);
	cpy = malloc(sizeof(char *) * size);
	while (env[i])
	{
		if (i == id)
			j--;
		else
			cpy[j] = ft_strdup(env[i]);
		j++;
		i++;
	}
	cpy[j] = NULL;
	free_dbl_array(env);
	return (cpy);
}

void	ft_unset(char **unset, t_shell *shell)
{
	int		i;
	int		j;
	char	**cpy;
	char	*name;

	i = 1;
	cpy = cpy_env(shell->env);
	check_unset(unset[i], 0, 0, 0);
	while (unset[i])
	{
		j = 0;
		while (cpy[j])
		{
			name = get_env_name(cpy[j]);
			if (match(unset[i], name))
			{
				cpy = ft_del_env(cpy, check_env_name(unset[i], cpy));
				j--;
			}
			j++;
			free(name);
		}
		i++;
	}
	replace_env(shell, cpy);
}
