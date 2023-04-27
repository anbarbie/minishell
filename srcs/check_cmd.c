/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:26:51 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 18:21:37 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**replace_cmd(char **old_array, char **new_array, int start)
{
	int	i;
	int	j;

	i = 0;
	j = start;
	while (old_array[start])
	{
		start++;
		i++;
	}
	new_array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (old_array[j])
	{
		new_array[i] = ft_strdup(old_array[j]);
		j++;
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	check_cmd(t_cmd *cmd)
{
	int		i;
	char	**new_cmd_array;

	i = 0;
	new_cmd_array = NULL;
	while (cmd->cmd_array[i])
	{
		if (cmd->cmd_array[i][0] != '\0')
		{
			new_cmd_array = replace_cmd(cmd->cmd_array, new_cmd_array, i);
			free(cmd->cmd);
			cmd->cmd = ft_strdup(cmd->cmd_array[i]);
			free_dbl_array(cmd->cmd_array);
			cmd->cmd_array = new_cmd_array;
			add_cmd_type(cmd);
			return ;
		}
		i++;
	}
}

void	check_cmd_list(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->cmd)
			if (cmd->cmd[0] == '\0')
				check_cmd(cmd);
		cmd = cmd->next;
	}
}
