/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:28:36 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 17:21:31 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_out_builtins(t_shell *shell, t_redir *redir)
{
	int	fd;

	if (redir->redir_type == REDIR_OUT)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
		{
			perror("minishell");
			return (0);
		}
		shell->fd_out = fd;
	}
	if (redir->redir_type == APPEND)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
		{
			perror("minishell");
			return (0);
		}
		shell->fd_out = fd;
	}
	return (1);
}

int	heredoc_builtins(t_shell *shell, t_redir *redir)
{
	int	fd;
	int	fd2;

	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("minishell");
		return (0);
	}
	read_until_delimitor(fd, redir->filename);
	fd2 = open(".tmp", O_RDONLY, 0777);
	if (fd2 < 0)
	{
		perror("minishell");
		return (0);
	}
	close(fd);
	unlink(".tmp");
	shell->fd_in = fd2;
	return (1);
}

int	redir_in_builtins(t_shell *shell, t_redir *redir)
{
	int	fd;

	if (redir->redir_type == HEREDOC)
		return (heredoc_builtins(shell, redir));
	if (redir->redir_type == REDIR_IN)
	{
		fd = open(redir->filename, O_RDONLY, 0777);
		if (fd < 0)
		{
			perror("minishell");
			return (0);
		}
		shell->fd_in = fd;
	}
	return (1);
}

int	redir_builtins(t_shell *shell, t_redir *redir)
{
	while (redir)
	{
		if (redir->redir_type == REDIR_OUT || redir->redir_type == APPEND)
			if (redir_out_builtins(shell, redir) == 0)
				return (0);
		if (redir->redir_type == REDIR_IN || redir->redir_type == HEREDOC)
			if (redir_in_builtins(shell, redir) == 0)
				return (0);
		redir = redir->next;
	}
	if (shell->fd_in != STDIN_FILENO)
		dup2(shell->fd_in, STDIN_FILENO);
	if (shell->fd_out != STDOUT_FILENO)
		dup2(shell->fd_out, STDOUT_FILENO);
	return (1);
}
