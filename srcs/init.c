/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:27:20 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 18:27:49 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->env = cpy_env(envp);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	g_ret = 0;
	return ;
}

void	init_aux(t_aux *aux, char **envp, t_cmd *cmd)
{
	aux->path = NULL;
	aux->path = ft_strdup("PATH");
	aux->path = cpy_env_line(aux->path, envp);
	aux->folders = NULL;
	aux->folders = ft_split(aux->path, ':');
	aux->tmp = NULL;
	aux->tmp = ft_strjoin_2("/", cmd->cmd);
}
