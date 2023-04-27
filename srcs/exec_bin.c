/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:10:32 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 15:37:19 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_bin(t_shell *shell, t_cmd *cmd)
{
	redir(shell, cmd->redir);
	if (shell->fd_in != STDIN_FILENO)
		dup2(shell->fd_in, STDIN_FILENO);
	if (shell->fd_out != STDOUT_FILENO)
		dup2(shell->fd_out, STDOUT_FILENO);
	if (!find_char(cmd->cmd, '/'))
		get_cmd_path(cmd, shell->env);
	if (execve(cmd->cmd, cmd->cmd_array, shell->env))
	{
		perror("minishell");
		g_ret = 127;
		free_everything(shell);
		exit(g_ret);
	}
}

void	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		exec_bin(shell, cmd);
	else
	{
		waitpid(pid, &g_ret, 0);
		if (WIFSIGNALED(g_ret))
		{
			g_ret = WTERMSIG(g_ret);
			g_ret = g_ret + 128;
		}
		else
			g_ret = WEXITSTATUS(g_ret);
	}
}
