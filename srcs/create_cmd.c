/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:56:02 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 19:30:14 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_cmd(t_token **token, t_cmd *new_cmd)
{
	int	i;
	int	got_cmd;

	i = 0;
	got_cmd = 0;
	while ((*token) != NULL && (*token)->type != PIPE)
	{
		if ((*token)->type == ARG)
		{
			if (!got_cmd)
			{
				got_cmd++;
				get_cmd_2(token, new_cmd, i);
			}
			else
			{
				i++;
				new_cmd->cmd_array[i] = ft_strdup((*token)->content);
			}
		}
		if (is_redir(token))
			create_redir(new_cmd, token);
		(*token) = (*token)->next;
	}
	return (i);
}

void	create_cmd(t_cmd **cmd, t_token **token, int n_of_args)
{
	t_cmd	*new_cmd;
	int		i;

	i = 0;
	new_cmd = create_new_cmd(n_of_args);
	i = get_cmd(token, new_cmd);
	if (n_of_args)
	{
		i++;
		new_cmd->cmd_array[i] = NULL;
	}
	add_cmd(cmd, new_cmd);
}

int	count_n_args(t_token **token, int n_args)
{
	t_token	*temp;

	temp = (*token);
	while (temp && temp->type != PIPE)
	{
		if (temp->type == ARG)
		{
			if (temp->previous)
			{
				if (temp->previous->type != REDIR_IN
					&& temp->previous->type != REDIR_OUT
					&& temp->previous->type != APPEND
					&& temp->previous->type != HEREDOC)
					n_args++;
			}
			else
				n_args++;
		}
		temp = temp->next;
	}
	return (n_args);
}

void	create_cmd_list(t_shell *shell, t_token *token)
{
	t_cmd	*cmd;
	int		n_of_args;

	cmd = NULL;
	while (token)
	{
		n_of_args = 0;
		n_of_args = count_n_args(&token, n_of_args);
		create_cmd(&cmd, &token, n_of_args);
		if (token)
			token = token->next;
	}
	shell->cmd = cmd;
}
