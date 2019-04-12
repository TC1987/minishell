/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:22:08 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 21:13:15 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "header.h"

char	*ft_strrem(const char *str, int start)
{
	int		i;
	size_t	length;
	char	*result;

	i = 0;
	length = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (length - start + 1));
	while (str[start + i])
	{
		result[i] = str[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strnjoin(const char *str1, const char *str2, const char *str3)
{
	int		i;
	int		j;
	size_t	length;
	char	*result;

	i = 0;
	j = 0;
	length = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	if (!(result = (char *)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	while (str1[i])
		result[j++] = str1[i++];
	i = 0;
	while (str2[i])
		result[j++] = str2[i++];
	i = 0;
	while (str3[i])
		result[j++] = str3[i++];
	result[j] = '\0';
	return (result);
}

void	free_double(char ***arr)
{
	int i;

	i = 0;
	if (arr && *arr)
	{
		while ((*arr)[i])
		{
			free((*arr)[i]);
			i++;
		}
		free(*arr);
	}
}

void	clean(char ***env)
{
	int i;

	i = 0;
	while ((*env)[i])
	{
		free((*env)[i]);
		i++;
	}
	free(*env);
}
