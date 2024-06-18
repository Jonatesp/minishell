/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:33:50 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 17:46:52 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_rvalue;

char	*ft_args_join(char **tmp)
{
	int		i;
	char	*ret;

	if (!tmp[1])
		return (NULL);
	ret = ft_strdup(tmp[1]);
	i = 1;
	while (tmp[++i])
	{
		ret = ft_strjoin(ret, " ");
		ret = ft_strjoin(ret, tmp[i]);
	}
	return (ret);
}

void	ft_handler_b(int b)
{
	(void)b;
}

void	ft_handler_c(int c)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*spaces;
	char	*prompt;
	int		i;

	(void)c;
	if (g_rvalue >= 0)
	{
		tmp = ft_strjoin(getcwd(cwd, sizeof(cwd)), "$> ");
		spaces = malloc(sizeof(char) * rl_point + 1);
		if (!spaces)
			return ;
		i = -1;
		while (++i < rl_point)
			spaces[i] = ' ';
		spaces[i] = '\0';
		prompt = ft_strjoin(tmp, spaces);
		ft_handler_c2(prompt, spaces, tmp);
		g_rvalue = 1;
	}
}

void	ft_disable_signal_print(char **env)
{
	pid_t	pid;
	char	**args;

	g_rvalue = 0;
	args = malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("stty");
	args[1] = ft_strdup("-echoctl");
	args[2] = 0;
	pid = fork();
	while (pid == 0)
	{
		execve("/bin/stty", args, env);
		return ;
	}
	if (pid != 0)
		waitpid(pid, 0, 0);
	free(args[0]);
	free(args[1]);
	free(args);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	t_split	*tmp;
	char	**my_env;

	if (argc > 1 || argv[1])
		return (0);
	my_env = ft_env_create(env);
	ft_disable_signal_print(my_env);
	signal(SIGQUIT, ft_handler_b);
	signal(SIGINT, ft_handler_c);
	while (1)
	{
		tmp = ft_reader(my_env);
		if (tmp)
		{
			cmd = parser(lexer(tmp), my_env);
			if (cmd)
				my_env = ft_main_util(cmd, my_env);
		}
	}
	return (0);
}
