/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 02:00:04 by tcho              #+#    #+#             */
/*   Updated: 2018/12/10 14:49:25 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

extern int g_display_path;

char	**init_environ(void);
void	free_double(char ***arr);
char	*get_env_value(char **env, char *name);
char	**get_paths(char **env);
char	*find_exec_path(char *command, char **env);
int		is_quote(char c);
int		remove_quotes(char **command);
char	*ft_strrem(const char *str, int start);
int		expand(char **command, char **env);
char	*ft_strnjoin(const char *str1, const char *str2, const char *str3);
int		get_env_index(char **env, char *name);
void	remove_element(char **command, size_t i);

int		error(char *subject, char *message, int status);

void	display(char **arr);

char	**split_input(char *buffer);

char	*get_env_key(char *env_str);

#endif
