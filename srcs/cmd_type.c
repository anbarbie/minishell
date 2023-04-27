/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:49:41 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/19 17:13:11 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strncmp_both(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0
		&& ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}

void	add_cmd_type(t_cmd *cmd)
{
	if (ft_strncmp_both(cmd->cmd, "echo") == 0)
		cmd->type = ECHO;
	else if (ft_strncmp_both(cmd->cmd, "cd") == 0)
		cmd->type = CD;
	else if (ft_strncmp_both(cmd->cmd, "pwd") == 0)
		cmd->type = PWD;
	else if (ft_strncmp_both(cmd->cmd, "export") == 0)
		cmd->type = EXPORT;
	else if (ft_strncmp_both(cmd->cmd, "unset") == 0)
		cmd->type = UNSET;
	else if (ft_strncmp_both(cmd->cmd, "env") == 0)
		cmd->type = ENV;
	else if (ft_strncmp_both(cmd->cmd, "exit") == 0)
		cmd->type = EXIT;
	else if (ft_strncmp(cmd->cmd, "./", ft_strlen("./")) == 0)
		cmd->type = EXEC;
	else
		cmd->type = CMD;
}
