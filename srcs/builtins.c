/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:58:14 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 18:21:57 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_builtins(t_cmd *cmd)
{
	if (ft_strstr(cmd->command, "echo") && ft_strlen(cmd->command) == 4)
		return (1);
	else if (ft_strstr(cmd->command, "cd") && ft_strlen(cmd->command) == 2)
		return (1);
	else if (ft_strstr(cmd->command, "pwd") && ft_strlen(cmd->command) == 3)
		return (1);
	else if (ft_strstr(cmd->command, "export") && ft_strlen(cmd->command) == 6)
		return (1);
	else if (ft_strstr(cmd->command, "unset") && ft_strlen(cmd->command) == 5)
		return (1);
	else if (ft_strstr(cmd->command, "env") && ft_strlen(cmd->command) == 3)
		return (1);
	else if (ft_strstr(cmd->command, "exit") && ft_strlen(cmd->command) == 4)
		return (1);
	else
		return (0);
}

char	**ft_cd(char *input, char **env, char **to_free, t_cmd *c)
{
	char	*cpy;
	char	**env_cpy;

	g_rvalue = 0;
	ft_free_args(NULL, to_free);
	env_cpy = ft_env_copy(env);
	if (!input || !input[0])
	{
		cpy = ft_getenv("HOME", env);
		if (cpy == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_rvalue = 1;
			free(cpy);
			return (env_cpy);
		}
		else if (!cpy[0])
		{
			free(cpy);
			return (env_cpy);
		}
	}
	else
		cpy = ft_strdup(input);
	return (ft_cd2(cpy, env_cpy, c));
}

/* flag = 0, 1 si -n */

void	ft_echo(char *input)
{
	char	*str;

	if (!input || !input[0])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_rvalue = 0;
		return ;
	}
	str = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!str)
	{
		g_rvalue = 1;
		return ;
	}
	ft_echo2(input, str, 0, -1);
	g_rvalue = 0;
	free(str);
	return ;
}

void	ft_pwd(int fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
		g_rvalue = 0;
	}
	else
	{
		perror("pwd");
		g_rvalue = 1;
	}
	return ;
}

void	ft_exit(t_cmd *c, char **my_env, char **args, char *str)
{
	int	code;
	int	i;

	ft_putstr_fd("exit\n", 1);
	if (!args || !args[0])
	{
		ft_destroyer(c, my_env, args, str);
		exit (g_rvalue);
	}
	if (args[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_rvalue = 1;
		return ;
	}
	i = -1;
	while (args[0][++i])
	{
		code = ft_exit3(args, i);
		if (code == 255)
			break ;
	}
	code = ft_exit2(args[0], code);
	ft_destroyer(c, my_env, args, str);
	exit(code);
}
