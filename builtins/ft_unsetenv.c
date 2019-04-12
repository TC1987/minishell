/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:58:32 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 01:28:55 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"
#include "listv.h"
#include "b_printf.h"
#include "libft.h"

int	ft_unsetenv(char **command, char ***env)
{
	int	i;
	int	length;

	i = 1;
	length = ft_listv_length(command);
	if (length == 1)
		b_printf("unsetenv: Too few arguments.\n");
	while (command[i])
	{
		if (ft_strequ(command[i], "PATH"))
			g_display_path = 0;
		else
			ft_listv_remove(env, get_env_index(*env, command[i]));
		i++;
	}
	return (1);
}
