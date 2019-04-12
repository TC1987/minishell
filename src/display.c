/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:16:35 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 21:13:52 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "header.h"
#include "b_printf.h"

int		error(char *subject, char *message, int status)
{
	if (subject)
	{
		b_printf("%s: %s\n", subject, message);
		free(subject);
	}
	else
		b_printf("%s\n", message);
	return (status);
}

void	display(char **list)
{
	int i;

	i = 0;
	while (list[i])
	{
		b_printf("%s\n", list[i]);
		i++;
	}
}

void	display_prompt(char **env)
{
	char	*current_user;
	char	*current_path;

	current_user = get_env_value(env, "USER");
	current_path = (char *)malloc(sizeof(char) * 100);
	getcwd(current_path, 100);
	b_printf("\033[1;33m%s\033[0m@\033[0;32m%s $ \033[0m",
			current_user, current_path);
	free(current_user);
	free(current_path);
}
