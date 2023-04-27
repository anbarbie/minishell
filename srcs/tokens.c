/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:46:04 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:34:06 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_token(t_token **token, char *str)
{
	int	i;

	i = 0;
	if (is_special_char(str[i]) == 0)
		str = get_word(token, str);
	if (str[i] == '"')
		str = get_d_quotes(token, str);
	if (str[i] == '\'')
		str = get_s_quotes(token, str);
	if (str[i] == '|')
		str = get_pipe(token, str);
	if (str[i] == '>' || str[i] == '<')
		str = get_redirect(token, str);
	if (str[i] == ' ')
		str = get_space(token, str);
	return (str);
}

void	tokenize(t_shell *shell)
{
	int		i;
	char	*copy;
	t_token	*token;

	i = 0;
	copy = ft_strdup(shell->line);
	copy = ft_strtrim2(copy, " ");
	copy = expand(copy, shell->env);
	shell->token = NULL;
	token = NULL;
	while (copy[i])
		copy = get_token(&token, copy);
	shell->token = token;
	free(copy);
}
