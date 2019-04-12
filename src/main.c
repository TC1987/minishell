/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:28:02 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 02:17:15 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "b_printf.h"
#include "libft.h"
#include "get_next_line.h"
#include "header.h"
#include "builtins.h"
#include "listv.h"

void	sig_handler(int sig)
{
	sig = 0;
	b_printf("\033[2D\033[2P \n$> ");
}

char	**init_environ(char **environ)
{
	size_t	i;
	size_t	length;
	char	**env;

	i = 0;
	length = ft_listv_length(environ);
	env = (char **)malloc(sizeof(char *) * (length + 1));
	while (i < length)
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	loop(char ***env)
{
	char	*buffer;
	char	**command;

	while (1)
	{
		display_prompt(*env);
		get_next_line(0, &buffer);
		if ((command = split_input(buffer)) && lowercase_command(command)
				&& remove_quotes(command) && expand(command, *env))
		{
			if (do_operation(command, env) == -1)
				break ;
		}
		free(buffer);
		if (command)
			free_double(&command);
	}
	free(buffer);
	free_double(&command);
}

int		main(int argc, char **argv, char **environ)
{
	char **env;

	if (argc == 1)
	{
		argv = NULL;
		signal(SIGINT, sig_handler);
		env = init_environ(environ);
		loop(&env);
		clean(&env);
	}
	return (0);
}
