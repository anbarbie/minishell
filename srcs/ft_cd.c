/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:23:44 by antbarbi          #+#    #+#             */
/*   Updated: 2022/06/21 15:47:58 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_path(char *search, int delim, char **env)
{
	char	*cpy;
	int		id;

	id = check_env_name(search, env);
	cpy = ft_substr(env[id], delim, 9999);
	if (!cpy)
	{
		cpy = malloc(sizeof(char));
		cpy[0] = '\0';
	}
	return (cpy);
}

void	ft_cd_exp(char *oldpwd, char *pwd, t_shell *shell)
{
	int		i;
	char	**joined;

	i = 0;
	joined = malloc(sizeof(char *) * 4);
	joined[0] = ft_strdup("null");
	joined[1] = ft_strdup("OLDPWD=");
	joined[2] = ft_strdup("PWD=");
	joined[3] = NULL;
	while (joined[i])
	{
		if (i == 1)
			joined[i] = ft_strjoin(joined[i], oldpwd);
		if (i == 2)
			joined[i] = ft_strjoin(joined[i], pwd);
		i++;
	}
	ft_export(joined, shell);
	free_dbl_array(joined);
}

void	ft_cd_home(char **path, t_shell *shell, char *env_path, char *tmp)
{
	if (env_size(path) == 1)
	{
		env_path = get_env_path("HOME", 5, shell->env);
		if (chdir(env_path) == -1)
		{
			g_ret = 1;
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		}
		else
			ft_cd_exp(tmp, env_path, shell);
	}
	free(env_path);
}

void	ft_cd_oldpwd(char **path, t_shell *shell, char *env_path, char *tmp)
{
	if (env_size(path) == 2 && match(path[1], "-"))
	{
		env_path = get_env_path("OLDPWD", 7, shell->env);
		if (chdir(env_path) == -1)
		{
			g_ret = 1;
			ft_putendl_fd("bash: cd: OLDPWD not set", 2);
		}
		else
		{
			ft_cd_exp(tmp, env_path, shell);
			ft_pwd();
		}
	}
	free(env_path);
}

void	ft_cd(char **path, t_shell *shell)
{
	char	*env_path;
	char	*tmp;

	env_path = NULL;
	tmp = getcwd((char *) NULL, 0);
	ft_cd_home(path, shell, env_path, tmp);
	ft_cd_oldpwd(path, shell, env_path, tmp);
	if (env_size(path) == 2 && !match(path[1], "-"))
	{
		if (chdir(path[1]) == -1)
		{
			g_ret = 1;
			ft_putendl_fd("minishell: cd: No such file or directory", 2);
		}
		else
		{
			env_path = getcwd((char *) NULL, 0);
			ft_cd_exp(tmp, env_path, shell);
		}
	}
	if (env_size(path) > 2)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	free(env_path);
	free(tmp);
}
