/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:40:16 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/19 17:16:24 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*create_token(char *content)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->next = NULL;
	new_token->previous = NULL;
	free(content);
	return (new_token);
}

t_token	*create_token_space(char *content)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->next = NULL;
	new_token->previous = NULL;
	return (new_token);
}

void	add_token(t_token **token, t_token *new_token)
{
	t_token	*current_token;
	t_token	*previous_token;

	if (*token == NULL)
		*token = new_token;
	else
	{
		current_token = *token;
		while (current_token->next)
			current_token = current_token->next;
		previous_token = current_token;
		current_token->next = new_token;
		current_token->next->previous = previous_token;
		current_token->next->next = NULL;
	}
}
