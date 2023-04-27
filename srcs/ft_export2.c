/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:42:24 by antbarbi          #+#    #+#             */
/*   Updated: 2022/06/21 11:49:17 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	check_env_name(char *name, char **env)
{
	int		i;
	char	*env_name;
	char	*new_name;

	i = 0;
	new_name = get_env_name(name);
	while (env[i])
	{
		env_name = get_env_name(env[i]);
		if (match(env_name, new_name))
		{
			free(new_name);
			free(env_name);
			return (i);
		}
		free(env_name);
		i++;
	}
	free(new_name);
	return (i);
}

int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**ft_export_arg(char *export, char **envp)
{
	int		i;
	char	**cpy;

	i = 0;
	if (check_env_name(export, envp) == env_size(envp))
		cpy = malloc(sizeof(char *) * (env_size(envp) + 2));
	else
		cpy = malloc(sizeof(char *) * (env_size(envp) + 1));
	while (envp[i])
	{
		if (i == check_env_name(export, envp))
			cpy[i] = ft_strdup(export);
		else
			cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	if (check_env_name(export, envp) == env_size(envp))
	{
		cpy[i] = ft_strdup(export);
		i++;
	}
	free_dbl_array(envp);
	cpy[i] = NULL;
	return (cpy);
}
