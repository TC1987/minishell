/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:29:21 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 01:32:33 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "b_printf.h"
#include "listv.h"
#include "header.h"
#include "libft.h"

void	update_path(char ***env, char *path)
{
	ft_listv_remove(env, get_env_index(*env, "OLDPWD"));
	ft_listv_add("OLDPWD", path, env);
	getcwd(path, 256);
	ft_listv_remove(env, get_env_index(*env, "PWD"));
	ft_listv_add("PWD", path, env);
}

char	*get_directory(char **command, char ***env)
{
	char *directory;

	directory = command[1] ? command[1] : get_env_value(*env, "HOME");
	if ((ft_strlen(directory) == 1) && directory[0] == '-')
		directory = get_env_value(*env, "OLDPWD");
	else if (ft_strequ(directory, "--"))
		directory = get_env_value(*env, "HOME");
	return (directory);
}

int		ft_cd(char **command, char ***env)
{
	int		result;
	char	path[256];
	char	*directory;

	directory = get_directory(command, env);
	getcwd(path, 256);
	if ((result = chdir(directory)) < 0)
	{
		if (command[1])
			b_printf("cd: no such file or directory: %s\n", command[1]);
	}
	else
		update_path(env, path);
	if (!ft_strequ(command[1], directory))
		free(directory);
	return (1);
}
