/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:46:26 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/19 17:23:15 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_word(t_token **token, char *str)
{
	int		i;
	int		j;
	t_token	*new_token;

	i = 0;
	j = 0;
	new_token = NULL;
	if (is_special_char(str[i]) == 0)
	{
		while (str[i] && is_special_char(str[i]) == 0)
			i++;
		new_token = create_token(cpy_portion(str, j, i));
		new_token->type = WORD;
		add_token(token, new_token);
	}
	str = extract_str(str, i);
	return (str);
}

char	*get_pipe(t_token **token, char *str)
{
	int		i;
	int		j;
	t_token	*new_token;

	i = 0;
	j = 0;
	if (str[i] == '|')
	{
		while (str[i] == '|' || str[i] == ' ')
			i++;
		new_token = create_token(cpy_portion(str, j, i));
		new_token->type = PIPE;
		add_token(token, new_token);
	}
	str = extract_str(str, i);
	return (str);
}

char	*get_redirect(t_token **token, char *str)
{
	int		i;
	int		j;
	t_token	*new_token;

	i = 0;
	j = 0;
	if (str[i] == '>' || str[i] == '<')
	{
		while (str[i] == '>' || str[i] == '<' || str[i] == ' ')
			i++;
		new_token = create_token(cpy_portion(str, j, i));
		new_token->type = REDIR;
		add_token(token, new_token);
	}
	str = extract_str(str, i);
	return (str);
}

char	*get_space(t_token **token, char *str)
{
	t_token	*new_token;

	new_token = create_token_space(" ");
	new_token->type = BLANK;
	add_token(token, new_token);
	str = ft_strtrim2(str, " ");
	return (str);
}
