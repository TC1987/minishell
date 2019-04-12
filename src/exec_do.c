/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:33:45 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 02:21:02 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "header.h"
#include "b_printf.h"
#include "builtins.h"

char	*find_exec_path(char *command, char **env)
{
	int		i;
	char	**paths;
	char	*full_path;

	i = 0;
	paths = get_paths(env);
	if (paths)
	{
		while (paths[i])
		{
			full_path = ft_strnjoin(paths[i], "/", command);
			if ((access(full_path, F_OK) == 0))
				break ;
			free(full_path);
			i++;
		}
		free_double(&paths);
		return (full_path);
	}
	return (NULL);
}

void	run_executable(char **command, char **env)
{
	char *exec_path;

	exec_path = find_exec_path(command[0], env) ?
		find_exec_path(command[0], env) : command[0];
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
			signal(SIGINT, sig_handler);
			waitpid(child_pid, &stat_loc, WUNTRACED);
			signal(SIGINT, sig_handler);
		}
	}
	return (status);
}
