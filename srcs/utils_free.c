/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:55:29 by requinch          #+#    #+#             */
/*   Updated: 2022/05/11 21:25:16 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*free_3_ret_4(void *first, void *second, void *third, void *fourth)
{
	if (first)
		free(first);
	if (second)
		free(second);
	if (third)
		free(third);
	return (fourth);
}

void	free_4(void	*first, void *second, void *third, void *fourth)
{
	if (first)
		free(first);
	if (second)
		free(second);
	if (third)
		free(third);
	if (fourth)
		free(fourth);
}

void	ft_free_args(char *str, char **args)
{
	int	i;

	i = -1;
	if (args)
	{
		while (args[++i])
			free(args[i]);
		free(args);
	}
	if (str)
		free(str);
	return ;
}

char	**free_1_ret_2(void *first, char **second)
{
	if (first)
		free(first);
	return (second);
}
