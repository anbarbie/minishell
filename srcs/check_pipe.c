/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:00:02 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 18:23:17 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipe(t_token **token)
{
	(*token)->content = ft_strtrim2((*token)->content, " ");
	if ((*token)->previous == NULL
		|| ft_strlen((*token)->content) >= 2
		|| (*token)->next == NULL)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_ret = 2;
		return (0);
	}
	return (1);
}
