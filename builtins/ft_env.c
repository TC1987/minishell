/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:26:43 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 01:33:33 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "b_printf.h"
#include "libft.h"
#include "header.h"

int g_display_path = 1;

int	ft_env(char **command, char ***env)
{
	int		i;
	char	*key;

	i = 0;
	command = NULL;
	while ((*env)[i])
	{
		key = get_env_key((*env)[i]);
		if (ft_strequ(key, "PATH") && !g_display_path)
		{
			free(key);
			i++;
			continue;
		}
		b_printf("%s\n", (*env)[i]);
		free(key);
		i++;
	}
	return (1);
}
