/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 23:31:39 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 16:27:56 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "b_printf.h"
#include "listv.h"
#include "builtins.h"
#include "header.h"

extern char **environ;

void display(char **list)
{
	int i;

	i = 0;
	while (list[i])
	{
		b_printf("%s\n", list[i]);
		i++;
	}
}

char **init_environ(void)
{
	size_t	i;
	size_t	length;
	char	**env;

	i = 0;
	length = ft_listv_length(environ);
	env = (char **)malloc(sizeof(char *) * (length + 1));
	while (i < length)
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

char *ft_strnjoin(const char *str1, const char *str2, const char *str3)
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

void free_double(char ***arr)
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

char *get_env_key(char *env_str)
{
	char	*result;
	char	**split_result;

	split_result = ft_strsplit(env_str, '=');
	result = ft_strdup(split_result[0]);
	free_double(&split_result);
	return (result);
}

int get_env_index(char **env, char *name)
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

char *get_env_value(char **env, char *name)
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
			result = split_result[1] ? ft_strdup(split_result[1]) : ft_strdup("");
			free_double(&split_result);
            return (result);
		}
        free_double(&split_result);
        i++;
    }
    return (NULL);
}

char **get_paths(char **env)
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

char *find_exec_path(char *command, char **env)
{
	int		i;
    char	**paths;
    char	*full_path;

	i = 0;
    paths = get_paths(env);
	if (paths)
	{
		while (paths[i])
		{
			full_path = ft_strnjoin(paths[i], "/", command);
			if ((access(full_path, F_OK) == 0))
				break;
			free(full_path);
			i++;
		}
		free_double(&paths);
		return (full_path);	
	}
    return (NULL);
}

int is_quote(char c)
{
    return (c == '\'' || c == '\"');
}

int remove_quotes(char **command)
{
    int		i;
    size_t	length;
    char	*result;

    i = 0;
    if (command && *command)
    {
        while (command[i])
        {
            length = ft_strlen(command[i]);
            if (is_quote(command[i][0]) && is_quote(command[i][length - 1]))
            {
                result = ft_strndup(command[i] + 1, length - 2);
                free(command[i]);
                command[i] = result;
            }
            i++;
        }
    }
	return (1);
}

char *ft_strrem(const char *str, int start)
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

char *get_full_path(char **env, char *str, int index)
{
    int     start;
    char    *env_key;
    char    *env_value;
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
	return (NULL);
}

int replace_tilde(char **command, char **env, int i)
{
	char *sub_string;
	char *home_dir;

	sub_string = NULL;
	home_dir = NULL;
	if (command[i][0] == '~' && command[i][1] != '~')
	{
		if ((home_dir = get_env_value(env, "HOME")))
		{
			sub_string = ft_strsub(command[i], 1, ft_strlen(command[i] - 1));
			free(command[i]);
			command[i] = ft_strjoin(home_dir, sub_string);
		}
	}
	return (1);
}

char *dollar_sign_removed(char *str)
{
	int index = 1;

	while (str[index] && (str[index] >= 33 && str[index] <= 126))
		index++;
	return (ft_strsub(str, 1, index - 1));
}

int replace_dollar_sign(char **command, char **env, int index)
{
	int		i;
	char	*result;

   	i = 0;
	result = NULL;
	while (command[index][i])
	{
		if (command[index][i] == '$' && ft_strlen(command[index]) > 1)
		{
			if ((result = get_full_path(env, command[index], i)))
			{
				free(command[index]);
				command[index] = result;
				if (ft_strcmp(result, "") == 0)
					i--;
			}
			else
				return (error(dollar_sign_removed(command[index]), "Undefined variable.", 0));
		}
		i++;
	}
	return (1);
}

int expand(char **command, char **env)
{
    size_t	i;

    i = 0;
	if (command && *command)
	{
		while (command[i])
		{
			if (ft_strequ(command[i], "$PATH") && !g_display_path)
				return (error(NULL, "PATH: Undefined variable.", 0));
			else if (replace_dollar_sign(command, env, i) == 0)
				return (0);
			replace_tilde(command, env, i);
			i++;
		}
	}
	return (1);
}
