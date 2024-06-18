/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:30:09 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 17:00:33 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**builtin_alone_routine(t_cmd *cmds, char **env)
{
	char	**args;
	char	*str;
	char	**ret;
	int		defstd[2];

	args = ft_args_copy(cmds, env);
	str = ft_join(args, cmds);
	defstd[0] = dup(STDIN_FILENO);
	defstd[1] = dup(STDOUT_FILENO);
	ft_close_fds(cmds, 0);
	ret = ft_exec_builtins(cmds, env, str, args);
	if (cmds->fd_in != STDIN_FILENO)
		dup2(defstd[0], STDIN_FILENO);
	if (cmds->fd_out != STDOUT_FILENO)
		dup2(defstd[1], STDOUT_FILENO);
	ft_free_args(str, args);
	return (ret);
}

void	children_subroutine(t_cmd *c, char *filepath, char **env)
{
	char	**args;
	char	*str;
	char	**args2;

	filepath = ft_executable2(filepath, c, -1, env);
	ft_close_fds(c, 0);
	args = ft_args_copy(c, env);
	str = ft_join(args, c);
	if (ft_find_builtins(c))
		ft_exec_builtins_childs(c, env, str, args);
	else
	{
		if (filepath == NULL)
		{
			ft_exec_errors(args, c, env, 2 - !(ft_strchr(c->command, '/')));
			free(str);
			exit (127);
		}
		args2 = ft_get_arg(c, args);
		execve(filepath, args2, env);
		ft_free_args(NULL, args2);
	}
	free(filepath);
	ft_destroyer(c, env, args, str);
	exit (g_rvalue);
}

pid_t	*procreate(t_cmd *cmds, char *filepath, char **env)
{
	pid_t	*pid;

	pid = ft_calloc(50, sizeof(pid_t));
	pid[0] = 0;
	while (cmds)
	{
		pid[0]++;
		if (ft_strcmp(cmds->command, "cat") == 0)
			g_rvalue = -1;
		pid[pid[0]] = fork();
		if (pid[pid[0]])
			cmds = cmds->next;
		else
			break ;
	}
	if (!pid[pid[0]])
	{
		children_subroutine(cmds, filepath, env);
		return (0);
	}
	else
		return (pid);
}

char	**ft_executable(t_cmd *cmds, char *filepath, char **env)
{
	int		status;
	pid_t	*pid;

	status = 0;
	if (!cmds->next && ft_find_builtins(cmds))
		return (builtin_alone_routine(cmds, env));
	filepath = ft_path_gev(filepath, env);
	if (!ft_strchr(filepath, '/'))
		filepath = free_3_ret_4(filepath, NULL, NULL, NULL);
	pid = procreate(cmds, filepath, env);
	if (filepath)
		free(filepath);
	ft_close_fds(cmds, 1);
	while (pid[0])
	{
		waitpid(pid[pid[0]], &status, 0);
		pid[0]--;
	}
	free(pid);
	g_rvalue = WEXITSTATUS(status);
	return (ft_env_copy(env));
}

char	*ft_executable2(char *filepath, t_cmd *c, int a, char **env)
{
	int	i;

	if (filepath == NULL)
	{
		i = 0;
		filepath = ft_get_path(c->command, ++i, ft_getenv("PATH", env));
		while (a == -1 && filepath != NULL)
		{
			a = access(filepath, F_OK & X_OK);
			if (ft_check_filepath(a, filepath, c) == 0)
				break ;
			free(filepath);
			filepath = ft_get_path(c->command, ++i, ft_getenv("PATH", env));
		}
		if (filepath)
			free(filepath);
		if (a == 0)
			return (ft_get_path(c->command, i, ft_getenv("PATH", env)));
		else
			return (NULL);
	}
	else
		filepath = ft_check_path(filepath, ft_path_gev(filepath, env));
	return (filepath);
}
