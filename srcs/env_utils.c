/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:28:36 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:03:14 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_env(t_shell *shell, char **cpy)
{
	free_dbl_array(shell->env);
	shell->env = NULL;
	shell->env = cpy;
}

char	*remove_char(char	*src, int to_remove)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(src) - to_remove + 1));
	while (src[i + to_remove])
	{
		result[i] = src[i + to_remove];
		i++;
	}
	result[i] = '\0';
	free(src);
	return (result);
}

int	right_line(char *to_find, char *line)
{
	if (ft_strnstr(line, to_find, ft_strlen(to_find)))
		return (1);
	return (0);
}

char	*cpy_env_line(char *to_find, char **envp)
{
	int		i;
	char	*result;

	i = 0;
	to_find = ft_strjoin(to_find, "=");
	while (envp[i])
	{
		if (right_line(to_find, envp[i]))
		{
			result = ft_strdup(envp[i]);
			result = remove_char(result, ft_strlen(to_find));
			free(to_find);
			return (result);
		}
		i++;
	}
	free(to_find);
	result = ft_strdup("\0");
	return (result);
}

char	**cpy_env(char	**envp)
{
	int		i;
	char	**cpy;

	i = 0;
	while (envp[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
