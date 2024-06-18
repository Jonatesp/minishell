/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:30:09 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 18:16:21 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_path(char *arg, int pos, char *var_path)
{
	char	*tmp;
	int		i[2];

	if (!var_path)
		return (NULL);
	i[0] = -1;
	tmp = malloc(sizeof(char) * (ft_strlen(var_path) + 2));
	if (!tmp)
		return (NULL);
	while (pos)
	{
		i[0]++;
		i[1] = -1;
		while (var_path[i[0]] && var_path[i[0]] != ':')
			tmp[++i[1]] = var_path[i[0]++];
		if (!var_path[i[0]])
			return (free_3_ret_4(tmp, var_path, NULL, NULL));
		pos--;
	}
	tmp[++i[1]] = '/';
	tmp[++i[1]] = '\0';
	free(var_path);
	return (ft_get_path2(tmp, arg));
}

char	*ft_get_path2(char *tmp, char *arg)
{
	char	*ret;

	ret = ft_strjoin(tmp, arg);
	free(tmp);
	return (ret);
}

char	**ft_exec_builtins(t_cmd *cmd, char **env, char *str, char **args)
{
	char	**args2;

	args2 = ft_split(str, ' ');
	if (ft_strstr(cmd->command, "echo") && ft_strlen(cmd->command) == 4)
		ft_echo(str);
	else if (ft_strstr(cmd->command, "cd") && ft_strlen(cmd->command) == 2)
		return (ft_cd(str, env, args2, cmd));
	else if (ft_strstr(cmd->command, "pwd") && ft_strlen(cmd->command) == 3)
		ft_pwd(1);
	else if (ft_strstr(cmd->command, "export") && ft_strlen(cmd->command) == 6)
		return (ft_export(args2, env));
	else if (ft_strstr(cmd->command, "unset") && ft_strlen(cmd->command) == 5)
		return (ft_unset(args2, env));
	else if (ft_strstr(cmd->command, "env") && ft_strlen(cmd->command) == 3)
		ft_env(env);
	else if (ft_strstr(cmd->command, "exit") && ft_strlen(cmd->command) == 4)
		ft_exit(cmd, env, args, str);
	ft_free_args(NULL, args2);
	return (ft_env_copy(env));
}

void	ft_exec_builtins_childs(t_cmd *cmd, char **env, char *str, char **args)
{
	char	**args2;
	char	**ret;

	args2 = ft_split(str, ' ');
	ret = NULL;
	if (ft_strstr(cmd->command, "echo") && ft_strlen(cmd->command) == 4)
		ft_echo(str);
	else if (ft_strstr(cmd->command, "cd") && ft_strlen(cmd->command) == 2)
		ret = ft_cd(str, env, args2, cmd);
	else if (ft_strstr(cmd->command, "pwd") && ft_strlen(cmd->command) == 3)
		ft_pwd(1);
	else if (ft_strstr(cmd->command, "export") && ft_strlen(cmd->command) == 6)
		ret = ft_export(args2, env);
	else if (ft_strstr(cmd->command, "unset") && ft_strlen(cmd->command) == 5)
		ret = ft_unset(args2, env);
	else if (ft_strstr(cmd->command, "env") && ft_strlen(cmd->command) == 3)
		ft_env(env);
	else if (ft_strstr(cmd->command, "exit") && ft_strlen(cmd->command) == 4)
		ft_exit_child(cmd, env, args, str);
	if (!ft_strstr(cmd->command, "cd") && ft_strlen(cmd->command) != 2)
		ft_free_args(NULL, args2);
	ft_free_args(NULL, ret);
}

char	*ft_path_gev(char *path, char **env)
{
	char	*tmp[2];

	if (path == NULL)
		return (NULL);
	tmp[0] = ft_strdup(path);
	tmp[1] = 0;
	gev(tmp, env);
	return (tmp[0]);
}
