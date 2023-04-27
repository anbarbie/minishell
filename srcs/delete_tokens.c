/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:54:34 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/23 19:45:18 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_blank(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token;
	shell->token = shell->token->next;
	shell->token->previous = NULL;
	free(tmp->content);
	free(tmp);
}

void	delete_space(t_token *token)
{
	while (token)
	{
		if (token->type == BLANK)
			delete_token(&token);
		token = token->next;
	}
}

void	delete_token(t_token **token)
{
	t_token	*temp;

	temp = (*token);
	if ((*token)->next == NULL)
	{
		(*token) = temp->previous;
		(*token)->next = NULL;
		free(temp->content);
		free(temp);
	}
	else
	{
		(*token) = temp->previous;
		(*token)->next = temp->next;
		(*token)->next->previous = (*token);
		free(temp->content);
		free(temp);
	}
}
