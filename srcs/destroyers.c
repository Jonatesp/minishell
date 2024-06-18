/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:45:16 by requinch          #+#    #+#             */
/*   Updated: 2022/05/12 17:42:58 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*destroy_toklist(t_toklist *toklist, t_cmd *parsed)
{
	if (!toklist)
		return (parsed);
	if (toklist->next)
		destroy_toklist(toklist->next, NULL);
	if (toklist->value)
		free(toklist->value);
	free(toklist->spaces);
	free(toklist);
	return (parsed);
}

t_toklist	*destroy_split(t_split *split, t_toklist *toklist)
{
	int	i;

	i = -1;
	while (split->args[++i])
		free(split->args[i]);
	free(split->args);
	free(split->spaces);
	free(split);
	return (word_interpreter(toklist, toklist));
}

void	destroy_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*save;

	while (cmd)
	{
		i = -1;
		free(cmd->command);
		if (cmd->arg)
		{
			while (cmd->arg[++i])
				free(cmd->arg[i]);
			free(cmd->arg);
		}
		free(cmd->spaces);
		save = cmd;
		cmd = cmd->next;
		free(save);
	}
}

void	ft_destroyer(t_cmd *c, char **my_env, char **args, char *str)
{
	int	i;

	i = -1;
	while (my_env[++i])
		free(my_env[i]);
	free(my_env);
	i = -1;
	if (args != NULL)
	{
		while (args[++i])
			free(args[i]);
		free(args);
	}
	if (str)
		free(str);
	destroy_cmd(c);
	rl_clear_history();
	return ;
}
