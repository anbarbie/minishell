/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:47:31 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/19 17:24:27 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_end_quote(char *str, char c, int start)
{
	int	n;

	n = 0;
	while (str[start])
	{
		if (str[start] == c)
			n++;
		start++;
	}
	return (n);
}

char	*get_d_quotes(t_token **token, char *str)
{
	int		i;
	int		j;
	t_token	*new_token;

	i = 0;
	j = 0;
	if (str[i] == '"')
	{
		if (find_end_quote(str, '"', i) == 2)
		{
			i++;
			while (str[i] != '"')
				i++;
			i++;
			new_token = create_token(cpy_portion(str, j, i));
			new_token->type = D_QUOTES;
			add_token(token, new_token);
		}
		else
			i++;
	}
	str = extract_str(str, i);
	return (str);
}

char	*get_s_quotes(t_token **token, char *str)
{
	int		i;
	int		j;
	t_token	*new_token;

	i = 0;
	j = 0;
	if (str[i] == '\'')
	{
		if (find_end_quote(str, '\'', i) == 2)
		{
			i++;
			while (str[i] != '\'')
				i++;
			i++;
			new_token = create_token(cpy_portion(str, j, i));
			new_token->type = S_QUOTES;
			add_token(token, new_token);
		}
		else
			i++;
	}
	str = extract_str(str, i);
	return (str);
}
