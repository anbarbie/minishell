/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:55:27 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 18:22:53 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	assign_filename_to_redir(t_token *token)
{
	while (token)
	{
		if (token->type == REDIR_IN
			|| token->type == REDIR_OUT
			|| token->type == APPEND
			|| token->type == HEREDOC)
			token->next->type = FILENAME;
		token = token->next;
	}
}

int	check_right_redir(t_token **token)
{
	if ((*token)->content[1] == '>')
	{
		(*token)->type = APPEND;
		return (1);
	}
	else if ((*token)->content[1] == '\0')
	{
		(*token)->type = REDIR_OUT;
		return (1);
	}
	ft_putstr_fd("minishell: syntax error\n", 2);
	return (0);
}

int	check_left_redir(t_token **token)
{
	if ((*token)->content[1] == '<')
	{
		(*token)->type = HEREDOC;
		return (1);
	}
	if ((*token)->content[1] == '\0')
	{
		(*token)->type = REDIR_IN;
		return (1);
	}
	ft_putstr_fd("minishell: syntax error\n", 2);
	return (0);
}

int	check_redir(t_token **token)
{
	(*token)->content = ft_strtrim2((*token)->content, " ");
	if (ft_strlen((*token)->content) >= 3
		|| (*token)->next == NULL
		|| (*token)->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_ret = 2;
		return (0);
	}
	if ((*token)->content[0] == '>' && ft_strlen((*token)->content) <= 3)
		return (check_right_redir(token));
	if ((*token)->content[0] == '<' && ft_strlen((*token)->content) <= 3)
		return (check_left_redir(token));
	return (1);
}
