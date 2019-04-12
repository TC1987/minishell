/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:07:36 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 01:27:45 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "libft.h"

int		is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int		remove_quotes(char **command)
{
	int		i;
	size_t	length;
	char	*result;

	i = 0;
	if (command && *command)
	{
		while (command[i])
		{
			length = ft_strlen(command[i]);
			if (is_quote(command[i][0]) && is_quote(command[i][length - 1]))
			{
				result = ft_strndup(command[i] + 1, length - 2);
				free(command[i]);
				command[i] = result;
			}
			i++;
		}
	}
	return (1);
}

char	*dollar_sign_removed(char *str)
{
	int index;

	index = 1;
	while (str[index] && (str[index] >= 33 && str[index] <= 126))
		index++;
	return (ft_strsub(str, 1, index - 1));
}

int		replace_dollar_sign(char **command, char **env, int index)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (command[index][i])
	{
		if (command[index][i] == '$' && ft_strlen(command[index]) > 1)
		{
			if ((result = get_full_path(env, command[index], i)))
			{
				free(command[index]);
				command[index] = result;
				if (ft_strcmp(result, "") == 0)
					i--;
			}
			else
				return (error(dollar_sign_removed(command[index]),
							"Undefined variable.", 0));
		}
		i++;
	}
	return (1);
}
