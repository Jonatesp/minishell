/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 04:06:01 by requinch          #+#    #+#             */
/*   Updated: 2022/05/12 15:51:07 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_token	what_is_this_shit(char *shit)
{
	if (shit[0] == 0)
		return (INVALID);
	else if (shit[0] == '<')
	{
		if (shit[1] == 0)
			return (INFILE);
		else if (shit[1] == '<' && shit[2] == 0)
			return (INSTDIN);
		else
			return (INVALID);
	}
	else if (shit[0] == '>')
	{
		if (shit[1] == 0)
			return (OUTFILE);
		else if (shit[1] == '>' && shit[2] == 0)
			return (APPEND);
		else
			return (INVALID);
	}
	else if (shit[0] == '|' && shit[1] == 0)
		return (PIPE);
	else
		return (WORD);
}

int	*duplicate_spaces(int *spaces, int start, int size)
{
	int	*lol;
	int	i;

	i = -1;
	if (size < 1)
	{
		size = 0;
		while (spaces[size] != -1)
			size++;
	}
	lol = malloc((size + 1) * sizeof(int));
	if (size == 0)
	{
		lol[0] = -1;
		return (lol);
	}
	while (spaces[start] != -1 && (size - (++i)))
		lol[i] = spaces[start + i];
	lol[i] = -1;
	return (lol);
}

t_toklist	*lexer_1(t_split *read, t_toklist *prev, int i)
{
	t_toklist	*toklist;

	toklist = ft_calloc(1, sizeof(t_toklist));
	if (!toklist)
		return (NULL);
	toklist->prev = prev;
	toklist->next = NULL;
	toklist->type = what_is_this_shit(read->args[i]);
	toklist->value = ft_strdup(read->args[i]);
	toklist->spaces = duplicate_spaces(read->spaces, i, 0);
	return (toklist);
}

t_toklist	*lexer(t_split *read)
{
	t_toklist	*toklist;
	t_toklist	*save;
	int			i;

	i = -1;
	if (!read)
		return (NULL);
	toklist = lexer_1(read, NULL, 0);
	if (!toklist)
		return ((t_toklist *)destroy_toklist(toklist, NULL));
	save = toklist;
	while (read->args[++i])
	{
		if (!i)
			continue ;
		toklist->next = lexer_1(read, toklist, i);
		if (!toklist->next)
			return ((t_toklist *)destroy_toklist(save, NULL));
		toklist = toklist->next;
	}
	return (destroy_split(read, save));
}
