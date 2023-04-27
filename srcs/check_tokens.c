/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:02:17 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/19 17:09:29 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_type(t_token **token, char **envp)
{
	if ((*token)->type == WORD)
		return (check_word(token, envp));
	if ((*token)->type == REDIR)
		return (check_redir(token));
	if ((*token)->type == S_QUOTES)
		return (check_squotes(token));
	if ((*token)->type == D_QUOTES)
		return (check_dquotes(token, envp));
	if ((*token)->type == PIPE)
		return (check_pipe(token));
	if ((*token)->type == BLANK)
		return (1);
	return (0);
}

int	check_tokens(t_shell *shell, t_token *token)
{
	while (token)
	{
		if (!add_type(&token, shell->env))
			return (0);
		token = token->next;
	}
	return (1);
}
