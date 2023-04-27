/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:41:19 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:14:47 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_ret;

void	launch_shell(t_shell *shell)
{
	add_history(shell->line);
	tokenize(shell);
	if (shell->token)
	{
		if (check_tokens(shell, shell->token))
		{
			assign_filename_to_redir(shell->token);
			create_cmd_list(shell, shell->token);
			check_cmd_list(shell->cmd);
			exec(shell, shell->cmd);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	g_ret = 0;
	while (1)
	{
		catch_signals();
		shell.fd_in = STDIN_FILENO;
		shell.fd_out = STDOUT_FILENO;
		shell.line = readline("minishell$ ");
		if (!shell.line)
			free_and_close(&shell);
		if (shell.line[0] != '\0')
			launch_shell(&shell);
		free_shell(&shell);
	}
	close(shell.std_in);
	close(shell.std_out);
	free_everything(&shell);
}
