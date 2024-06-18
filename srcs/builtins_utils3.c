/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:35:59 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 15:37:53 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo3(char *str, int flag)
{
	char	*tmp;

	if (str[0])
	{
		if (flag == 0)
			tmp = ft_strjoin(str, "\n");
		else
			tmp = ft_strdup(str);
		ft_putstr_fd(tmp, STDOUT_FILENO);
		free(tmp);
	}
}

void	ft_print_env_alpha3(char **tmp)
{
	int	*i;

	i = malloc(sizeof(int) * 3);
	if (!i)
		return ;
	i[0] = -1;
	while (tmp[++i[0]])
	{
		i[2] = 0;
		ft_putstr_fd("declare -x ", 1);
		i[1] = -1;
		while (tmp[i[0]][++i[1]] && tmp[i[0]][i[1]] != '=')
			ft_putchar_fd(tmp[i[0]][i[1]], 1);
		if (!tmp[i[0]][i[1]])
			ft_putchar_fd('\n', 1);
		else
		{
			ft_putchar_fd(tmp[i[0]][i[1]], 1);
			ft_print_env_alpha4(tmp, i);
		}
	}
	free(i);
}

void	ft_print_env_alpha4(char **tmp, int *i)
{
	if (tmp[i[0]][i[1]] == '=')
		i[2] = 1;
	if (i[2])
		ft_putchar_fd('\"', 1);
	if (tmp[i[0]][++i[1]])
		while (tmp[i[0]][i[1]])
			ft_putchar_fd(tmp[i[0]][i[1]++], 1);
	if (i[2])
		ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}

char	*ft_getenv(char *str, char **env)
{
	int		i;
	int		j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && str[j] && env[i][j] == str[j] && env[i][j] != '=')
		{
			j++;
			if (env[i][j] == '=' && !str[j] && str[j - 1] == env[i][j - 1])
				return (ft_getenv2(env, i, j));
		}
	}
	return (NULL);
}

char	*ft_getenv2(char **env, int i, int j)
{
	int		k;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
	if (!ret)
		return (NULL);
	k = -1;
	if (env[i][j + 1])
	{
		while (env[i][++j])
			ret[++k] = env[i][j];
	}
	ret[++k] = '\0';
	return (ret);
}
