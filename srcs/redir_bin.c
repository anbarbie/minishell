/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:51:03 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/23 12:18:48 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_until_delimitor(int fd, char	*delimitor)
{
	char	*line;

	line = NULL;
	ft_putstr_fd("heredoc> ", 1);
	while (get_next_line_2(STDIN_FILENO, &line, delimitor))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = NULL;
		ft_putstr_fd("heredoc> ", 1);
	}
	if (line)
		free(line);
	return ;
}

void	redir_out(t_shell *shell, t_redir *redir)
{
	int	fd;

	if (redir->redir_type == REDIR_OUT)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
		{
			perror("minishell");
			free_everything(shell);
			exit(EXIT_FAILURE);
		}
		shell->fd_out = fd;
	}
	if (redir->redir_type == APPEND)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
		{
			perror("minishell");
			free_everything(shell);
			exit(EXIT_FAILURE);
		}
		shell->fd_out = fd;
	}
}

void	heredoc(t_shell *shell, t_redir *redir)
{
	int	fd;
	int	fd2;

	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("minishell");
		free_everything(shell);
		exit(EXIT_FAILURE);
	}
	read_until_delimitor(fd, redir->filename);
	fd2 = open(".tmp", O_RDONLY, 0777);
	if (fd2 < 0)
	{
		perror("minishell");
		free_everything(shell);
		exit(EXIT_FAILURE);
	}
	close(fd);
	unlink(".tmp");
	shell->fd_in = fd2;
}

void	redir_in(t_shell *shell, t_redir *redir)
{
	int	fd;

	if (redir->redir_type == HEREDOC)
		heredoc(shell, redir);
	if (redir->redir_type == REDIR_IN)
	{
		fd = open(redir->filename, O_RDONLY, 0777);
		if (fd < 0)
		{
			perror("minishell");
			free_everything(shell);
			exit(EXIT_FAILURE);
		}
		shell->fd_in = fd;
	}
}

void	redir(t_shell *shell, t_redir *redir)
{
	while (redir)
	{
		if (redir->redir_type == REDIR_OUT || redir->redir_type == APPEND)
			redir_out(shell, redir);
		if (redir->redir_type == REDIR_IN || redir->redir_type == HEREDOC)
			redir_in(shell, redir);
		redir = redir->next;
	}
}
