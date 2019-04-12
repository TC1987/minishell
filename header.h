/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 02:00:04 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 02:14:23 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <string.h>

extern int g_display_path;

int		get_env_index(char **env, char *name);
char	*get_full_path(char **env, char *str, int index);
char	*get_env_key(char *env_str);
char	*get_env_value(char **env, char *name);
char	**get_paths(char **env);
int		is_quote(char c);
int		remove_quotes(char **command);
char	*dollar_sign_removed(char *str);
int		replace_dollar_sign(char **command, char **env, int index);
int		error(char *subject, char *message, int status);
void	display(char **arr);
void	display_prompt(char **env);
char	*ft_strrem(const char *str, int start);
char	*ft_strnjoin(const char *str1, const char *str2, const char *str3);
void	free_double(char ***arr);
void	clean(char ***env);
void	sig_handler(int sig);
int		replace_tilde(char **command, char **env, int i);
int		lowercase_command(char **command);
int		expand(char **command, char **env);
char	*find_exec_path(char *command, char **env);
void	run_executable(char **command, char **env);
int		do_builtin(char **command, char ***env);
int		do_operation(char **command, char ***env);
char	**init_environ(char **environ);
char	**split_input(char *buffer);
void	remove_element(char **command, size_t i);

#endif
