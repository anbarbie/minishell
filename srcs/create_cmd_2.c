/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:29:57 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 19:33:12 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_cmd(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*current_cmd;
	t_cmd	*previous_cmd;

	if (*cmd == NULL)
		*cmd = new_cmd;
	else
	{
		current_cmd = *cmd;
		while (current_cmd->next)
			current_cmd = current_cmd->next;
		previous_cmd = current_cmd;
		current_cmd->next = new_cmd;
		current_cmd->next->previous = previous_cmd;
		current_cmd->next->next = NULL;
	}
}

t_cmd	*create_new_cmd(int n_of_args)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->cmd = NULL;
	new_cmd->cmd_array = NULL;
	if (n_of_args)
		new_cmd->cmd_array = malloc(sizeof(char *) * (n_of_args + 1));
	new_cmd->type = NO_CMD;
	new_cmd->next = NULL;
	new_cmd->previous = NULL;
	new_cmd->redir = NULL;
	return (new_cmd);
}

void	get_cmd_2(t_token **token, t_cmd *new_cmd, int i)
{
	new_cmd->cmd = ft_strdup((*token)->content);
	new_cmd->cmd_array[i] = ft_strdup((*token)->content);
	add_cmd_type(new_cmd);
}

int	is_redir(t_token **token)
{
	if ((*token)->type == REDIR_IN
		|| (*token)->type == REDIR_OUT
		|| (*token)->type == APPEND
		|| (*token)->type == HEREDOC)
		return (1);
	return (0);
}
