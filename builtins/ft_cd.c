/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:29:21 by tcho              #+#    #+#             */
/*   Updated: 2018/12/09 01:11:32 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Can change to a directory using /.
// Can cd into ~ or $

#include <stdlib.h>
#include <unistd.h>
#include "b_printf.h"
#include "listv.h"
#include "header.h"
#include "libft.h"

void update_path(char ***env, char *path)
{
	ft_listv_remove(env, get_env_index(*env, "OLDPWD"));
	ft_listv_add("OLDPWD", path, env);
	getcwd(path, 100);
	ft_listv_remove(env, get_env_index(*env, "PWD"));
	ft_listv_add("PWD", path, env);
	free(path);
}

char *get_directory(char **command, char ***env)
{
	char *directory;

	directory = command[1] ? command[1] : get_env_value(*env, "HOME");
	if ((ft_strlen(directory) == 1) && directory[0] == '-')
		directory = get_env_value(*env, "OLDPWD"); 
	else if (ft_strcmp(directory, "--") == 0)
		directory = get_env_value(*env, "HOME");
	return (directory);
}

int ft_cd(char **command, char ***env)
{
	int		result;
	char	*path;
	char	*directory;

	path = (char *)malloc(sizeof(char) * 100);
	directory = get_directory(command, env);
	getcwd(path, 100);
	if ((result = chdir(directory)) < 0)
	{
		if (command[1])
			b_printf("cd: no such file or directory: %s\n", command[1]);
	}
	else
		update_path(env, path);
	return (1);
}
