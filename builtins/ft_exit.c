/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:25:31 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 01:28:21 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "b_printf.h"

int	ft_exit(char **command, char ***env)
{
	command = NULL;
	env = NULL;
	b_printf("exit\n");
	return (-1);
}
