/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:10:48 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 18:20:17 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_redir(t_redir **redir, t_redir *new_redir)
{
	t_redir	*temp;

	if ((*redir) == NULL)
		(*redir) = new_redir;
	else
	{
		temp = (*redir);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redir;
	}
}

void	create_redir(t_cmd *cmd, t_token **token)
{
	t_redir	*new_redir;

	new_redir = NULL;
	new_redir = malloc(sizeof(t_redir));
	new_redir->filename = NULL;
	new_redir->redir_type = (*token)->type;
	(*token) = (*token)->next;
	new_redir->filename = ft_strdup((*token)->content);
	new_redir->next = NULL;
	add_redir(&(cmd->redir), new_redir);
}
