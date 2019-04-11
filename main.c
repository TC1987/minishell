/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:28:02 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 10:15:39 by tcho             ###   ########.fr       */
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

int		error(char *subject, char *message, int status)
{
	if (subject)
		b_printf("%s: %s\n", subject, message);
	else
		b_printf("%s\n", message);
	return (status);
}

int		do_builtin(char **command, char ***env)
{
	int					i;
	static t_builtins	operations[] = {
		{ "cd", ft_cd },
		{ "echo", ft_echo },
		{ "env", ft_env },
		{ "printenv", ft_env },
		{ "exit", ft_exit },
		{ "setenv", ft_setenv },
		{ "unsetenv", ft_unsetenv },
	};

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(operations[i].name, command[0]) == 0)
			return (operations[i].function(command, env));
		i++;
	}
	return (0);
}

void	run_executable(char **command, char **env)
{
	char *exec_path;

	exec_path = (exec_path = find_exec_path(command[0], env)) ? exec_path : command[0];
	if ((access(exec_path, X_OK) == 0))
	{
		if (execve(exec_path, command, env) < 0)
			b_printf("minish: command not found: %s\n", command[0]);
	}
	else
	{
		if (access(exec_path, F_OK) == 0)
			b_printf("minish: permission denied\n");
		else
			b_printf("minish: command not found: %s\n", command[0]);
	}
	exit(1);
}

int		do_operation(char **command, char ***env)
{
	pid_t	child_pid;
	int		stat_loc;
	int		status;

	status = 0;
	if (command && *command && (status = do_builtin(command, env)) == 0)
	{
		child_pid = fork();
		if (child_pid < 0)
			b_printf("Error forking process.");
		else if (child_pid == 0)
			run_executable(command, *env);
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(child_pid, &stat_loc, WUNTRACED);
			signal(SIGINT, SIG_DFL);
		}
	}
	return (status);	
}

void	display_prompt(char **env)
{
	char *current_user;
	char *current_path; 

	current_user = get_env_value(env, "USER");
	current_path = (char *)malloc(sizeof(char) * 100);
	getcwd(current_path, 100);
	b_printf("\033[1;33m%s\033[0m@\033[0;32m%s $ \033[0m", current_user, current_path);
	free(current_user);
	free(current_path);
}

int		lowercase_command(char **command)
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

void	loop(char ***env)
{
	char	*buffer;
	char	**command;

	while (1)
	{
		display_prompt(*env);
		get_next_line(0, &buffer);
		if ((command = split_input(buffer)) && lowercase_command(command) && remove_quotes(command) && expand(command, *env))
		{
			if (do_operation(command, env) == -1)
				break;
		}
		free(buffer);
		if (command)
			free_double(&command);
	}
	// If the `if` statement runs and do_operation fails, need to free after breaking out of while loop.
	free(buffer);
	free_double(&command);
}

void	clean(char ***env)
{
	int i;

	i = 0;
	while ((*env)[i])
	{
		free((*env)[i]);
		i++;
	}
	free(*env);
}

void sig_handler(int sig)
{
	sig = 0;
	b_printf("\033[2D\033[2P \n$> ");
}

int		main(void)
{
	char **env;

	signal(SIGINT, sig_handler);
	env = init_environ();
	loop(&env);
	clean(&env);
}
