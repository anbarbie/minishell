/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:23:47 by antbarbi          #+#    #+#             */
/*   Updated: 2022/06/24 15:48:54 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env_check(char *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] == '=')
			cpt++;
		i++;
	}
	if (!cpt)
		return (0);
	return (1);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_env_check(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
}
