/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:37:56 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/10 12:11:15 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit2(char *arg, int code)
{
	int	value;

	if (code == 255)
		return (255);
	value = ft_atoi(arg);
	while (value > 0)
	{
		code += 1;
		if (code > 255)
			code = 0;
		value -= 1;
	}
	while (value < 0)
	{
		code -= 1;
		if (code < 0)
			code = 255;
		value += 1;
	}
	return (code);
}

int	ft_exit3(char **args, int i)
{
	if (!(args[0][i] >= 48 && args[0][i] <= 57) && args[0][i] != '-')
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	if (args[0][0] == '-' && !args[0][1])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	return (0);
}

char	*ft_remove_dollar(char *str, int j)
{
	int		i;
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] && i < j)
	{
		ret[i] = str[i];
		i++;
	}
	while (str[i + 1])
	{
		ret[i] = str[i + 1];
		i++;
	}
	free(str);
	return (ret);
}

int	ft_export3(char *str, char *tmp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		return (0);
	while (str[i] && str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	i = 0;
	while (ret[i] && ret[i] == tmp[i])
		i++;
	if (!ret[i] && ft_strlen(ret) == ft_strlen(tmp))
	{
		free(ret);
		return (1);
	}
	free(ret);
	return (0);
}

char	**ft_realloc_env(char **env, char *tmp)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (ft_args_size(env, 0) + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while (env[++i])
		ret[i] = ft_strdup(env[i]);
	ret[i] = ft_strdup(tmp);
	ret[i + 1] = 0;
	return (ret);
}
