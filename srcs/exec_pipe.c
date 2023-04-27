/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:11 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:10:09 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_bin_pipe(t_shell *shell, t_cmd *cmd, t_fd *fd, int *p)
{
	if (!find_char(cmd->cmd, '/'))
		get_cmd_path(cmd, shell->env);
	if (execve(cmd->cmd, cmd->cmd_array, shell->env))
	{
		perror("minishell");
		g_ret = 127;
		close_and_free_builtins(shell, p, fd);
	}
}

void	prepare_for_next_cmd(t_cmd *cmd, int *old_p, int *new_p)
{
	close(old_p[0]);
	close(old_p[1]);
	if (cmd->next)
	{
		old_p[0] = new_p[0];
		old_p[1] = new_p[1];
	}
}

void	exec_cmd_pipe(t_shell *shell, t_cmd *cmd, int *p)
{
	pid_t	pid;
	t_fd	*fd;
	int		new_p[2];

	fd = malloc(sizeof(fd));
	redir_pipe(shell, fd, cmd->redir);
	if (cmd->next)
		pipe(new_p);
	pid = fork();
	if (pid == -1)
	{
		g_ret = 1;
		close_and_free_builtins(shell, p, fd);
	}
	else if (pid == 0)
	{
		create_pipe(cmd, p, new_p);
		check_valid_fd(shell, fd, p);
		exec_cmd_pipe_2(shell, cmd, p, fd);
	}
	prepare_for_next_cmd(cmd, p, new_p);
	cmd->pid = pid;
	free(fd);
}

void	wait_for_exec(t_cmd *cmd)
{
	while (cmd)
	{
		waitpid(cmd->pid, &g_ret, 0);
		cmd = cmd->next;
	}
}

void	exec_pipe(t_shell *shell, t_cmd *cmd)
{
	int	p[2];

	pipe(p);
	while (cmd)
	{
		exec_cmd_pipe(shell, cmd, p);
		cmd = cmd->next;
	}
	wait_for_exec(shell->cmd);
	if (WIFSIGNALED(g_ret))
	{
		g_ret = WTERMSIG(g_ret);
		g_ret = g_ret + 128;
	}
	else
		g_ret = WEXITSTATUS(g_ret);
}
