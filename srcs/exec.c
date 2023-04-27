/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:57:01 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:24:19 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_builtins(t_shell *shell, t_cmd *cmd)
{
	if (!redir_builtins(shell, cmd->redir))
		return ;
	if (cmd->type == EXIT)
		ft_exit_single_cmd(shell, cmd);
	g_ret = 0;
	if (cmd->type == PWD)
		ft_pwd();
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

void	exec_single_cmd(t_shell *shell, t_cmd *cmd)
{
	if ((cmd->type == CMD || cmd->type == EXEC) && cmd->cmd[0] != '\0')
		exec_cmd(shell, cmd);
	else
		exec_builtins(shell, cmd);
	if (shell->fd_in != 0)
		close(shell->fd_in);
	if (shell->fd_out != 1)
		close(shell->fd_out);
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	catch_signals_exec();
	if (cmd->next)
		exec_pipe(shell, cmd);
	else
		exec_single_cmd(shell, cmd);
}
