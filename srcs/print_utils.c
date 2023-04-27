/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:33:05 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/19 17:26:06 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_dbl_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("STR %d = %s\n", i, str[i]);
		i++;
	}
}

void	print_tokens(t_shell *shell)
{
	while (shell->token->previous)
		shell->token = shell->token->previous;
	while (shell->token->next)
	{
		printf("TOKEN %s\n", shell->token->content);
		shell->token = shell->token->next;
	}
}

void	print_redir_list(t_redir *redir)
{
	while (redir)
	{
		printf("REDIR TYPE = %d\n", redir->redir_type);
		printf("REDIR FILENAME = %s\n", redir->filename);
		redir = redir->next;
	}
}
