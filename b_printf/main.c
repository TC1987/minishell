/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:53:10 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 10:32:45 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_printf.h"

int main(void)
{
	char *str = "WorldASD";
	b_printf("Hello %s %d\n", str, 100);
	while (1);
}
