/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:34:45 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 15:54:15 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_signal(char *result)
{
	char	*to_join;

	to_join = NULL;
	to_join = ft_itoa(g_ret);
	result = ft_strjoin(result, to_join);
	free(to_join);
	return (result);
}

void	expand_env(char *str, t_expand *exp, int j, char **envp)
{
	char	*to_join;

	to_join = NULL;
	to_join = replace_by_variable(str, j, exp->i, envp);
	exp->result = ft_strjoin(exp->result, to_join);
	free(to_join);
}

void	expand_check(t_expand *exp, char *str, char **envp)
{
	int	j;

	j = 0;
	if (str[exp->i] == '$' && str[exp->i + 1])
	{
		exp->i++;
		if (str[exp->i] == '?')
		{
			exp->result = expand_signal(exp->result);
			exp->i++;
		}
		else
		{
			j = exp->i;
			while (str[exp->i] && !ft_isset(str[exp->i], " /.$!:,'\"+-%%"))
				exp->i++;
			expand_env(str, exp, j, envp);
		}
	}
	else
	{
		exp->result = join_character(exp->result, str[exp->i]);
		exp->i++;
	}
}

char	*expand_dollar(char *str, char **envp)
{
	t_expand	*exp;
	char		*result;

	exp = malloc(sizeof(t_expand));
	exp->i = 0;
	exp->result = malloc(sizeof(char));
	exp->result[0] = '\0';
	while (str[exp->i])
		expand_check(exp, str, envp);
	free(str);
	result = ft_strdup(exp->result);
	free(exp->result);
	free(exp);
	return (result);
}
