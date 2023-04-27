/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:49:47 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 15:54:07 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_found_quote(t_expand *exp, char *str)
{
	char	c;

	c = str[exp->i];
	if (find_end_quote(str, c, exp->i) == 2)
	{
		exp->result = join_character(exp->result, str[exp->i]);
		exp->i++;
		while (str[exp->i] != c)
		{
			exp->result = join_character(exp->result, str[exp->i]);
			exp->i++;
		}
	}
	else
	{
		exp->result = join_character(exp->result, str[exp->i]);
		exp->i++;
	}
}

void	expand_found_dollar(t_expand *exp, char *str, char **envp)
{
	int	j;

	j = 0;
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

void	expand_base(t_expand *exp, char *str, char **envp)
{
	if (str[exp->i] == '\'' || str[exp->i] == '"')
		expand_found_quote(exp, str);
	else if (str[exp->i] == '$' && str[exp->i + 1])
		expand_found_dollar(exp, str, envp);
	else
	{
		exp->result = join_character(exp->result, str[exp->i]);
		exp->i++;
	}
}

char	*expand(char *str, char **envp)
{
	t_expand	*exp;
	char		*result;

	exp = malloc(sizeof(t_expand));
	exp->i = 0;
	exp->result = malloc(sizeof(char));
	exp->result[0] = '\0';
	while (str[exp->i])
		expand_base(exp, str, envp);
	free(str);
	result = ft_strdup(exp->result);
	free(exp->result);
	free(exp);
	return (result);
}
