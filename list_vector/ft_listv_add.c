/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstv_duplicate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 07:53:20 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 10:48:27 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "listv.h"
#include "header.h"
#include "libft.h"

void	ft_listv_add(char *name, char *value, char ***list)
{
	int		i;
	size_t	length;
	char	*new_env;
	char	**new_list;

	i = 0;
	length = ft_listv_length(*list);
	new_env = ft_strnjoin(name, "=", value);
	new_list = (char **)malloc(sizeof(char *) * (length + 2));
	while ((*list)[i])
	{
		new_list[i] = ft_strdup((*list)[i]);
		free((*list)[i]);
		i++;
	}
	new_list[i++] = new_env;
	new_list[i] = NULL;
	free(*list);
	*list = new_list;
}
