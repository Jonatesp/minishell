/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:12:35 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/11 21:35:04 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_args_copy(t_cmd *cmd, char **env)
{
	char	**ret;
	int		i;

	if (!cmd->arg || !cmd->arg[0])
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_args_size(cmd->arg, 0) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (cmd->arg[++i])
		ret[i] = ft_strdup(cmd->arg[i]);
	ret[i] = 0;
	gev(ret, env);
	return (ret);
}

char	*ft_iterate_shlvl(char *str)
{
	int		i;
	int		n;
	char	*ret;
	char	*tmp;
	char	*res;

	tmp = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(getenv("SHLVL"))));
	if (!tmp)
		return (NULL);
	i = -1;
	while (str[++i] != '=')
		tmp[i] = str[i];
	tmp[i] = str[i];
	tmp[i + 1] = '\0';
	n = ft_atoi(getenv("SHLVL")) + 1;
	res = ft_itoa(n);
	ret = ft_strjoin(tmp, res);
	return (free_3_ret_4(res, tmp, str, ret));
}

char	**ft_env_copy(char **env)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (ft_args_size(env, 0) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (env[++i])
		ret[i] = ft_strdup(env[i]);
	ret[i] = 0;
	return (ret);
}

int	ft_check_env(char *str, char *tmp)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
	{
		if (str[i] != tmp[i])
			return (0);
	}
	return (1);
}

void	ft_handler_c2(char *prompt, char *spaces, char *tmp)
{
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(prompt, 1);
	free(prompt);
	free(spaces);
	free(tmp);
	rl_redisplay();
}
