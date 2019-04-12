/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:28:08 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 02:02:10 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "builtins.h"
#include "listv.h"
#include "b_printf.h"
#include "libft.h"

extern int g_display_path;

int	ft_setenv(char **command, char ***env)
{
	int		length;

	length = ft_listv_length(command);
	if (length == 2 && ft_strchr(command[1], '='))
	{
		b_printf("setenv: Var name must contain alphanumeric characters.\n");
		return (1);
	}
	if (length == 1)
		ft_env(command, env);
	else if (length > 3)
		b_printf("setenv: Too many arguments.\n");
	else
	{
		ft_listv_remove(env, get_env_index(*env, command[1]));
		if (ft_strequ(command[1], "PATH"))
			g_display_path = 1;
		if (length == 3)
			ft_listv_add(command[1], command[2], env);
		else
			ft_listv_add(command[1], "", env);
	}
	return (1);
}
