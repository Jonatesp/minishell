/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:37:25 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/11 21:47:45 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_export(char **input, char **my_env)
{
	int		i;
	char	**ret;

	i = -1;
	g_rvalue = 0;
	if (!(input))
	{
		ft_print_env_alpha(my_env);
		return (ft_env_copy(my_env));
	}
	while (input[++i] != NULL)
	{
		if (ft_check_export_unset_input(input[i]) == 0)
			ret = ft_export2(input[i], my_env);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(input[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_rvalue = 1;
			ret = ft_env_copy(my_env);
		}
	}
	ft_free_args(NULL, input);
	return (ret);
}

char	**ft_unset(char **input, char **my_env)
{
	int		i;
	int		j;
	char	**ret;

	i = -1;
	g_rvalue = 0;
	if (!input || !input[0])
		return (my_env);
	while (input[++i])
	{
		j = -1;
		if (ft_check_export_unset_input(input[i]) == 0
			&& !ft_strchr(input[i], '='))
			ret = ft_unset2(input, i, j, my_env);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(input[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_rvalue = 1;
			ret = ft_env_copy(my_env);
		}
	}
	ft_free_args(NULL, input);
	return (ret);
}

char	**ft_export_replace(char *input, char **my_env)
{
	int		*j;
	char	*tmp;
	char	**ret;

	j = malloc(sizeof(int) * 2);
	if (!j)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!tmp)
		return (NULL);
	j[1] = -1;
	while (input[++j[1]] != '=' && input[j[1]])
		tmp[j[1]] = input[j[1]];
	tmp[j[1]] = '\0';
	ret = ft_export_replace2(ft_env_copy(my_env), tmp, input, j);
	if (j[0] == -1)
		return (free_1_ret_2(j, ret));
	j[0] = -1;
	while (ret[++j[0]])
		free(ret[j[0]]);
	free(ret);
	ret = ft_realloc_env(my_env, input);
	free(tmp);
	return (free_1_ret_2(j, ret));
}

char	**ft_export_replace2(char **env, char *tmp, char *input, int *i)
{
	int		j[3];
	char	**env_cpy;

	j[2] = -1;
	j[0] = -1;
	env_cpy = ft_env_copy(env);
	while (env[++j[2]] != NULL)
	{
		j[1] = -1;
		if (ft_check_env(env[j[2]], tmp))
		{
			ft_free_args(env_cpy[j[2]], env);
			env_cpy[j[2]] = ft_strdup(input);
			free(tmp);
			i[0] = -1;
			return (env_cpy);
		}
	}
	i[0] = j[2];
	ft_free_args(NULL, env);
	return (env_cpy);
}

int	ft_check_export_unset_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122)
			&& str[i] != 95 && str[i] != 61 && !(str[0] >= 48 && str[0] <= 57))
			return (1);
		i++;
	}
	if (str[i] == '=' && i == 0)
		return (2);
	return (0);
}
