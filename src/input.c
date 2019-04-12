/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 23:31:39 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 21:11:04 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "header.h"
#include "b_printf.h"

int	replace_tilde(char **command, char **env, int i)
{
	char *sub_string;
	char *home_dir;

	sub_string = NULL;
	home_dir = NULL;
	if (command[i][0] == '~' && command[i][1] != '~')
	{
		if ((home_dir = get_env_value(env, "HOME")))
		{
			sub_string = ft_strsub(command[i], 1, ft_strlen(command[i] - 1));
			free(command[i]);
			command[i] = ft_strjoin(home_dir, sub_string);
			free(sub_string);
			free(home_dir);
		}
	}
	return (1);
}

int	lowercase_command(char **command)
{
	size_t	i;
	size_t	length;
	char	*lowercase_exec;

	if (command && *command)
	{
		i = 0;
		length = ft_strlen(command[0]);
		lowercase_exec = (char *)malloc(sizeof(char) * (length + 1));
		while (command[0][i])
		{
			lowercase_exec[i] = ft_tolower(command[0][i]);
			i++;
		}
		lowercase_exec[i] = '\0';
		free(command[0]);
		command[0] = lowercase_exec;
	}
	return (1);
}

int	expand(char **command, char **env)
{
	size_t	i;

	i = 0;
	if (command && *command)
	{
		while (command[i])
		{
			if (ft_strequ(command[i], "$PATH") && !g_display_path)
				return (error(NULL, "PATH: Undefined variable.", 0));
			else if (replace_dollar_sign(command, env, i) == 0)
				return (0);
			replace_tilde(command, env, i);
			i++;
		}
	}
	return (1);
}
