/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 00:26:17 by tcho              #+#    #+#             */
/*   Updated: 2018/12/02 02:28:46 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTV_H
# define LISTV_H

size_t	ft_listv_length(char **list);
void	ft_listv_add(char *name, char *value, char ***list);
void	ft_listv_remove(char ***list, int i);

#endif
