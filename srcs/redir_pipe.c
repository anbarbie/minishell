/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:08:27 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:03:55 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_until_delimitor_pipe(t_shell *shell, int fd, char	*delimitor)
{
	char	*line;

	line = NULL;
	ft_putstr_fd("heredoc> ", 1);
	while (get_next_line_2(shell->std_in, &line, delimitor))
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

void	redir_out_pipe(t_shell *shell, t_fd *fds, t_redir *redir)
{
	int	fd;

	(void)shell;
	if (redir->redir_type == REDIR_OUT)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		fds->fd_out = fd;
	}
	if (redir->redir_type == APPEND)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		fds->fd_out = fd;
	}
}

void	heredoc_pipe(t_shell *shell, t_fd *fds, t_redir *redir)
{
	int	fd;
	int	fd2;

	fd2 = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd2 < 0)
	{
		perror("minishell");
		free(fds);
		free_everything(shell);
		exit(EXIT_FAILURE);
	}
	read_until_delimitor_pipe(shell, fd2, redir->filename);
	fd = open(".tmp", O_RDONLY, 0777);
	close(fd2);
	unlink(".tmp");
	fds->fd_in = fd;
}

void	redir_in_pipe(t_shell *shell, t_fd *fds, t_redir *redir)
{
	int	fd;

	if (redir->redir_type == HEREDOC)
	{
		heredoc_pipe(shell, fds, redir);
	}
	if (redir->redir_type == REDIR_IN)
	{
		fd = open(redir->filename, O_RDONLY, 0777);
		fds->fd_in = fd;
	}
}

void	redir_pipe(t_shell *shell, t_fd *fds, t_redir *redir)
{
	fds->fd_in = STDIN_FILENO;
	fds->fd_out = STDOUT_FILENO;
	while (redir)
	{
		if (redir->redir_type == REDIR_OUT || redir->redir_type == APPEND)
			redir_out_pipe(shell, fds, redir);
		if (redir->redir_type == REDIR_IN || redir->redir_type == HEREDOC)
			redir_in_pipe(shell, fds, redir);
		redir = redir->next;
	}
}
