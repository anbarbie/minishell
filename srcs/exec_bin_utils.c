/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:11:31 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 15:36:28 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*str;

	x = 0;
	y = 0;
	if (s1 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[x])
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		str[x] = s2[y];
		x++;
		y++;
	}
	str[x] = '\0';
	return (str);
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	get_cmd_path(t_cmd *cmd, char **envp)
{
	t_aux	*aux;
	char	*cmd_path;
	int		i;

	i = 0;
	aux = malloc(sizeof(t_aux));
	init_aux(aux, envp, cmd);
	cmd_path = NULL;
	while (aux->folders[i])
	{
		cmd_path = ft_strjoin_2(aux->folders[i], aux->tmp);
		if (access(cmd_path, F_OK) != -1)
		{
			free_aux(aux);
			free(cmd->cmd);
			cmd->cmd = cmd_path;
			return ;
		}
		free (cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_aux(aux);
	return ;
}

int	check_dbl_array_size(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}
