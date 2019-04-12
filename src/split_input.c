/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 06:54:12 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 21:32:07 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "header.h"
#include "b_printf.h"

int		verify_closing_quote(char *buffer, int i)
{
	char quote;

	quote = buffer[i++];
	while (buffer[i] && (buffer[i] != quote))
		i++;
	if (!buffer[i])
	{
		b_printf("Unmatched %c.\n", quote);
		return (-1);
	}
	return (i++);
}

int		count_words(char *buffer)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] != ' ')
		{
			count++;
			if (is_quote(buffer[i]))
				if ((i = verify_closing_quote(buffer, i)) == -1)
					return (-1);
			while (buffer[i] && (buffer[i] != ' '))
				i++;
		}
		while (buffer[i] && ft_isspace(buffer[i]))
			i++;
	}
	return (count);
}

int		insert_word(char **list, char *buffer, int *index, int i)
{
	int		j;
	char	quote;

	if (is_quote(buffer[i]))
	{
		quote = buffer[i];
		j = i + 1;
		while (buffer[j] && (buffer[j] != quote))
			j++;
		list[(*index)++] = ft_strsub(buffer, i + 1, j - i - 1);
		i = j + 1;
	}
	else
	{
		j = i;
		while (buffer[j] && !ft_isspace(buffer[j]))
			j++;
		list[(*index)++] = ft_strsub(buffer, i, j - i);
		i = j;
	}
	return (i);
}

char	**fill_list(char *buffer, int length)
{
	int		i;
	int		index;
	char	**list;

	i = 0;
	index = 0;
	if (!(list = (char **)malloc(sizeof(char *) * (length + 1))))
		return (NULL);
	while (buffer[i])
	{
		while (buffer[i] && ft_isspace(buffer[i]))
			i++;
		if (buffer[i])
			i = insert_word(list, buffer, &index, i);
	}
	list[index] = 0;
	return (list);
}

char	**split_input(char *buffer)
{
	int		word_count;

	word_count = 0;
	if (buffer)
	{
		if ((word_count = count_words(buffer)) > 0)
			return (fill_list(buffer, word_count));
	}
	return (NULL);
}
