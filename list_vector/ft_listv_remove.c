/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listv_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:41:22 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 15:59:06 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "listv.h"

#include "b_printf.h"

void	ft_listv_remove(char ***list, int i)
{
	int		length;

	length = ft_listv_length(*list);
	if (i >= 0)
	{
		free((*list)[i]);
		while (i < length)
		{
			(*list)[i] = (*list)[i + 1];
			i++;
		}
		(*list)[i] = 0;
	}
}
