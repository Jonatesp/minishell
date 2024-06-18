/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:53:49 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 00:31:21 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gev(char **args, char **my_env)
{
	int		i;
	int		q[3];
	char	*tmp;

	i = -1;
	if (!args || !args[0])
		return ;
	while (args[++i])
	{
		q[0] = 0;
		while (args[i][q[0]] && args[i][q[0]] != '\'' && args[i][q[0]] != '\"')
			q[0]++;
		q[2] = args[i][q[0]];
		q[1] = check_quotes_gev(args[i], q[0]);
		gev2(args, i, q, my_env);
		if (q[1] > 0)
		{
			tmp = ft_strdup(args[i]);
			free(args[i]);
			args[i] = ft_remove_quotes(tmp);
			free(tmp);
		}
	}
	return ;
}

void	gev2(char **args, int i, int *q, char **my_env)
{
	int	j;

	j = 0;
	while (args[i][j])
	{
		if (args[i][j] == '$' && q[2] == 34)
		{
			if (args[i][j + 1] == '\"')
				args[i] = ft_remove_dollar(args[i], j);
			else if (args[i][j + 1] == '?')
				args[i] = ft_last_return(args[i], j);
			else
				args[i] = ft_env_var_replace(args[i], my_env, j);
		}
		else if (args[i][j] == '$' && !(j > q[0] && j < q[1]))
		{
			if (args[i][j + 1] == '?')
				args[i] = ft_last_return(args[i], j);
			else
				args[i] = ft_env_var_replace(args[i], my_env, j);
		}
		else
			j++;
	}
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	char	type;
	char	*ret;

	if (str[0] == '\'' && str[1] == '\'' && str[2] != 0)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\'' && str[i] != '\"')
		ret[i] = str[i];
	type = str[i];
	while (str[i + 1] && str[i + 1] != type)
	{
		ret[i] = str[i + 1];
		i++;
	}
	while (str[i + 2])
	{
		ret[i] = str[i + 2];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	check_quotes_gev(char *str, int j)
{
	char	c;

	if (!str[j])
		return (0);
	c = str[j];
	while (str[++j])
	{
		if (str[j] == c)
			return (j);
	}
	return (0);
}

char	**ft_get_arg(t_cmd *cmd, char **args)
{
	char	**res;
	int		i;

	if (!args || args[0] == NULL)
		return (ft_split(cmd->command, ' '));
	res = malloc(sizeof(char *) * (ft_args_size(args, 0) + 2));
	res[0] = ft_strdup(cmd->command);
	i = -1;
	while (args[++i])
		res[i + 1] = ft_strdup(args[i]);
	res[i + 1] = 0;
	return (res);
}
