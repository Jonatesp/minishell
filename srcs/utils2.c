/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:05:54 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 18:06:50 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc_part_2(int fd, char *line)
{
	close(fd);
	free(line);
	fd = open(".heredoc", O_RDONLY);
	unlink(".heredoc");
	return (fd);
}

int	cnt_sp(int *spaces)
{
	int	i;

	i = 0;
	while (spaces[i] != -1)
		i++;
	return (i);
}

char	**ft_copy_args(t_cmd *cmd)
{
	char	**ret;
	int		i;

	if (!cmd->arg)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_args_size(cmd->arg, 0) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (cmd->arg[++i])
		ret[i] = ft_strdup(cmd->arg[i]);
	ret[i] = NULL;
	return (ret);
}

char	**ft_main_util(t_cmd *cmd, char **my_env)
{
	int		i;
	char	**env_cpy;

	env_cpy = ft_env_copy(my_env);
	i = -1;
	while (my_env[++i])
		free(my_env[i]);
	free(my_env);
	my_env = ft_executable(cmd, cmd->command, env_cpy);
	i = -1;
	while (env_cpy[++i])
		free(env_cpy[i]);
	free(env_cpy);
	destroy_cmd(cmd);
	return (my_env);
}
