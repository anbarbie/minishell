/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:29:26 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/19 17:21:47 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		free(redir->filename);
		temp = redir;
		redir = redir->next;
		free(temp);
	}
}

void	free_cmd(t_shell *shell)
{
	t_cmd	*previous_cmd;

	if (shell->cmd == NULL)
		return ;
	while (shell->cmd)
	{
		if (shell->cmd->redir)
			free_redir(shell->cmd->redir);
		if (shell->cmd->cmd)
			free(shell->cmd->cmd);
		if (shell->cmd->cmd_array)
			free_dbl_array(shell->cmd->cmd_array);
		previous_cmd = shell->cmd;
		shell->cmd = shell->cmd->next;
		free(previous_cmd);
	}
	free(shell->cmd);
}

void	free_tokens(t_shell *shell)
{
	t_token	*previous_token;

	if (shell->token == NULL)
		return ;
	while (shell->token)
	{
		free(shell->token->content);
		previous_token = shell->token;
		shell->token = shell->token->next;
		free(previous_token);
	}
	free (shell->token);
}

void	free_shell(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->token)
		free_tokens(shell);
	if (shell->cmd)
		free_cmd(shell);
	return ;
}

void	free_everything(t_shell *shell)
{
	if (shell->env)
		free_dbl_array(shell->env);
	free_shell(shell);
}
