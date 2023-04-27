/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:56:34 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:34:27 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_word(t_token **token, char **envp)
{
	(void)envp;
	if ((*token)->previous != NULL && (*token)->previous->type == ARG)
	{
		(*token)->previous->content
			= ft_strjoin((*token)->previous->content, (*token)->content);
		delete_token(token);
	}
	else
		(*token)->type = ARG;
	return (1);
}

int	check_dquotes(t_token **token, char **envp)
{
	(*token)->content = ft_strtrim2((*token)->content, "\"");
	(*token)->content = expand_dollar((*token)->content, envp);
	if ((*token)->previous != NULL && (*token)->previous->type == ARG)
	{
		(*token)->previous->content
			= ft_strjoin((*token)->previous->content, (*token)->content);
		delete_token(token);
	}
	else
		(*token)->type = ARG;
	return (1);
}

int	check_squotes(t_token **token)
{
	(*token)->content = ft_strtrim2((*token)->content, "'");
	if ((*token)->previous != NULL && (*token)->previous->type == ARG)
	{
		(*token)->previous->content
			= ft_strjoin((*token)->previous->content, (*token)->content);
		delete_token(token);
	}
	else
		(*token)->type = ARG;
	return (1);
}
