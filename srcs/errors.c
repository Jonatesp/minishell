/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:23:11 by requinch          #+#    #+#             */
/*   Updated: 2022/05/12 16:35:37 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_errors(char **args, t_cmd *cmds, char **env, int type)
{
	char	*tmp;

	tmp = ft_getenv("PATH", env);
	if (tmp == NULL)
		type = 2;
	else
		free(tmp);
	tmp = ft_path_gev(cmds->command, env);
	if (type == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	ft_destroyer(cmds, env, args, tmp);
}
