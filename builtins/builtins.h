/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 07:18:50 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 01:40:31 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct	s_builtins {
	char	*name;
	int		(*function)(char **args, char ***env);
}				t_builtins;

int				ft_cd(char **command, char ***env);
int				ft_echo(char **command, char ***env);
int				ft_env(char **command, char ***env);
int				ft_exit(char **command, char ***env);
int				ft_setenv(char **command, char ***env);
int				ft_unsetenv(char **command, char ***env);

#endif
