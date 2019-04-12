/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:03:40 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 21:12:49 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "libft.h"

char	*get_env_key(char *env_str)
{
	char	*result;
	char	**split_result;

	split_result = ft_strsplit(env_str, '=');
	result = ft_strdup(split_result[0]);
	free_double(&split_result);
	return (result);
}

int		get_env_index(char **env, char *name)
{
	int		i;
	char	**split_result;

	i = 0;
	while (env[i])
	{
		split_result = ft_strsplit(env[i], '=');
		if (ft_strequ(name, split_result[0]))
		{
			free_double(&split_result);
			return (i);
		}
		free_double(&split_result);
		i++;
	}
	return (-1);
}

char	*get_env_value(char **env, char *name)
{
	int		i;
	char	**split_result;
	char	*result;

	i = 0;
	while (env[i])
	{
		split_result = ft_strsplit(env[i], '=');
		if (ft_strequ(name, split_result[0]))
		{
			result = split_result[1] ? ft_strdup(split_result[1])
				: ft_strdup("");
			free_double(&split_result);
			return (result);
		}
		free_double(&split_result);
		i++;
	}
	return (NULL);
}

char	**get_paths(char **env)
{
	char *env_value;
	char **paths;

	env_value = get_env_value(env, "PATH");
	if (env_value)
	{
		paths = ft_strsplit(env_value, ':');
		free(env_value);
		return (paths);
	}
	return (NULL);
}

char	*get_full_path(char **env, char *str, int index)
{
	int		start;
	char	*env_key;
	char	*env_value;
	char	*sub_string;
	char	*joined;

	start = index;
	index++;
	while (str[index] && ft_isalpha(str[index]))
		index++;
	env_key = ft_strsub(str, start + 1, index - start - 1);
	if ((env_value = get_env_value(env, env_key)))
	{
		sub_string = ft_strndup(str, start);
		joined = ft_strnjoin(sub_string, env_value, str + index);
		free(sub_string);
		free(env_key);
		free(env_value);
		return (joined);
	}
	free(env_key);
	return (NULL);
}
