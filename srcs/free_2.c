/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:32:11 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:29:57 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_dbl_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_and_close(t_shell *shell)
{
	close(shell->std_in);
	close(shell->std_out);
	free_everything(shell);
	printf("exit\n");
	exit(g_ret);
}

void	free_aux(t_aux *aux)
{
	free(aux->tmp);
	free(aux->path);
	free_dbl_array(aux->folders);
	free(aux);
}

void	close_and_free_builtins(t_shell *shell, int *old_p, t_fd *fd)
{
	close(old_p[0]);
	close(old_p[1]);
	close(shell->std_in);
	close(shell->std_out);
	close(fd->fd_in);
	close(fd->fd_out);
	free(fd);
	free_everything(shell);
	exit(g_ret);
}
