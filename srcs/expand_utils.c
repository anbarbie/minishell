/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:07:30 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 15:07:59 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cpy_var(char	*src, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (end - start + 1));
	while (src[start] && i != end - start)
	{
		result[i] = src[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*replace_by_variable(char *src, int start, int end, char **envp)
{
	char	*env_line;
	char	*var;

	var = NULL;
	env_line = NULL;
	var = cpy_var(src, start, end);
	env_line = cpy_env_line(var, envp);
	return (env_line);
}

char	*join_character(char *str, char c)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (str == NULL)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	i++;
	result[i] = '\0';
	free(str);
	return (result);
}
