/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:22:08 by tcho              #+#    #+#             */
/*   Updated: 2018/12/09 05:38:13 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "b_printf.h"

int ft_echo(char **command, char ***env)
{
	int i;
	int space;

	i = 1;
	space = 0;
	env = NULL;
	while (command[i])
	{
		if (space)
			b_printf(" ");
		b_printf("%s", command[i]);
		space = 1;
		i++;
	}
	b_printf("\n");
	return (1);
}
