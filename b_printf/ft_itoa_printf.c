/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:33:06 by tcho              #+#    #+#             */
/*   Updated: 2018/11/28 23:20:41 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_printf.h"

int	ft_itoa_printf(int num)
{
	int count;

	count = 0;
	if (num == -2147483648)
		return (ft_ps("-2147483648"));
	else
	{
		if (num < 0)
		{
			ft_pc('-');
			num = -num;
			count++;
		}
		if (num >= 10)
			count += ft_itoa_printf(num / 10);
		ft_pc((num % 10) + '0');
		count++;
		return (count);
	}
}
