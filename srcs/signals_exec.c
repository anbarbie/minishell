/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:26:57 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/20 19:27:21 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	catch_sigint_exec(int sig)
{
	(void)sig;
	g_ret = 130;
	printf("\n");
}

void	catch_sigquit_exec(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	return ;
}

void	catch_signals_exec(void)
{
	signal(SIGINT, catch_sigint_exec);
	signal(SIGQUIT, catch_sigquit_exec);
}
