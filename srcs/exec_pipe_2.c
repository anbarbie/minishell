/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:31:15 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:25:10 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_builtins_and_free(t_shell *shell, t_cmd *cmd, int *p, t_fd *fd)
{
	exec_builtins_pipe(shell, cmd);
	close_and_free_builtins(shell, p, fd);
}

void	exec_builtins_pipe(t_shell *shell, t_cmd *cmd)
{
	if (cmd->type == EXIT)
		ft_exit_pipe(cmd);
	else
	{
		g_ret = 0;
		if (cmd->type == ECHO)
			ft_echo(cmd->cmd_array);
		if (cmd->type == UNSET)
			ft_unset(cmd->cmd_array, shell);
		if (cmd->type == ENV)
			ft_env(shell->env);
		if (cmd->type == EXPORT)
			ft_export(cmd->cmd_array, shell);
		if (cmd->type == CD)
			ft_cd(cmd->cmd_array, shell);
	}
}

void	exec_cmd_pipe_2(t_shell *shell, t_cmd *cmd, int *p, t_fd *fd)
{
	if ((cmd->type == CMD || cmd->type == EXEC) && cmd->cmd[0] != '\0')
		exec_bin_pipe(shell, cmd, fd, p);
	else
		exec_builtins_and_free(shell, cmd, p, fd);
	close_and_free_builtins(shell, p, fd);
}

void	check_valid_fd(t_shell *shell, t_fd *fd, int *p)
{
	if (fd->fd_in < 0 || fd->fd_out < 0)
	{
		g_ret = 1;
		perror("minishell");
		close_and_free_builtins(shell, p, fd);
	}
	if (fd->fd_in != STDIN_FILENO)
		dup2(fd->fd_in, STDIN_FILENO);
	if (fd->fd_out != STDOUT_FILENO)
		dup2(fd->fd_out, STDOUT_FILENO);
}

void	create_pipe(t_cmd *cmd, int *old_p, int *new_p)
{
	if (cmd->previous)
	{
		close(old_p[1]);
		dup2(old_p[0], STDIN_FILENO);
		close(old_p[0]);
	}
	if (cmd->next)
	{
		close(new_p[0]);
		dup2(new_p[1], STDOUT_FILENO);
		close(new_p[1]);
	}
}
