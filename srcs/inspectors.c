/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:59:39 by requinch          #+#    #+#             */
/*   Updated: 2022/05/11 23:46:23 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	coloscopy(char *str)
{
	int	i;

	i = -1;
	printf("Inspecting pointer :\n");
	printf("Address : \t%p\n", str);
	printf("Value :\t\t%s\n", str);
	printf("Characters :\t");
	if (str)
	{
		while (str && str[++i])
			printf("%i ", str[i]);
		printf("%i ", str[i]);
	}
	printf("\n\n");
}

void	inspecteur_poirot(t_cmd *cmd)
{
	int	j;

	printf("Inspecting commands list :\n");
	if (!cmd)
		printf("Cmd is empty, somehow. Pls fix\n");
	while (cmd)
	{
		j = -1;
		printf("Command :\t\t%s\n", cmd->command);
		while (cmd->arg && cmd->arg[++j])
		{
			printf("Space : \t\t%i\n", cmd->spaces[j]);
			printf("Argument %i :\t\t%s\n", j, cmd->arg[j]);
		}
		printf("Space : \t\t%i\n", cmd->spaces[j]);
		printf("Infile :\t\t%i\n", cmd->fd_in);
		printf("Outfile :\t\t%i\n", cmd->fd_out);
		if (cmd->prev)
			printf("Previous command :\t%s\n", cmd->prev->command);
		if (cmd->next)
			printf("Next command :\t\t%s\n", cmd->next->command);
		printf("\n");
		cmd = cmd->next;
	}
}

void	inspecteur_gadget(t_toklist *toklist)
{
	printf("Inspecting tokens list :\n");
	if (!toklist)
		printf("Toklist is empty, somehow. Pls fix\n");
	while (toklist)
	{
		printf("Value :\t\t\t%s\n", toklist->value);
		printf("Type :\t\t\t%i\n", toklist->type);
		printf("Space :\t\t\t%i\n", toklist->spaces[0]);
		if (toklist->prev)
			printf("Previous token :\t%s\n", toklist->prev->value);
		if (toklist->next)
			printf("Next token :\t\t%s\n", toklist->next->value);
		printf("\n");
		toklist = toklist->next;
	}
}
