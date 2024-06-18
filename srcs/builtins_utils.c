/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:10:07 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/11 21:05:04 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo2(char *input, char *str, int flag, int i)
{
	if (input[0] == '-' && input[1] == 'n')
	{
		ft_handle_echo_flag(str, input, i);
		flag = 1;
	}
	else
	{
		while (input[++i])
			str[i] = input[i];
		str[i] = '\0';
	}
	ft_echo3(str, flag);
}

char	**ft_export2(char *input, char **my_env)
{
	int		j;
	char	*tmp;
	char	**ret;

	if ((ft_strchr(input, '=')))
		ret = ft_export_replace(input, my_env);
	else
	{
		j = -1;
		tmp = ft_strcpy(input);
		while (my_env[++j])
		{
			if (ft_check_env(my_env[j], tmp) == 1)
				break ;
		}
		if (my_env[j] == NULL)
			ret = ft_realloc_env(my_env, tmp);
		else
			ret = ft_env_copy(my_env);
		free(tmp);
	}
	return (ret);
}

char	**ft_unset2(char **input, int i, int j, char **my_env)
{
	int		k;
	char	**ret;

	ret = ft_env_copy(my_env);
	while (ret[++j])
	{
		if (ft_strstr(ret[j], input[i]))
		{
			k = -1;
			while (ret[j + ++k + 1])
			{
				free(ret[j + k]);
				ret[j + k] = ft_strdup(ret[j + k + 1]);
			}
			free(ret[j + k]);
			ret[j + k] = NULL;
		}
	}
	return (ret);
}

void	ft_print_env_alpha(char **my_env)
{
	char	**tmp;
	int		len;
	int		i;

	len = ft_args_size(my_env, 0);
	tmp = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (my_env[++i])
		tmp[i] = ft_strdup(my_env[i]);
	tmp[i] = 0;
	ft_print_env_alpha2(len, tmp);
	ft_print_env_alpha3(tmp);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}

void	ft_print_env_alpha2(int len, char **tmp)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			if (ft_strcmp(tmp[j], tmp[j + 1]) > 0)
			{
				temp = ft_strdup(tmp[j]);
				free(tmp[j]);
				tmp[j] = ft_strdup(tmp[j + 1]);
				free(tmp[j + 1]);
				tmp[j + 1] = ft_strdup(temp);
				free(temp);
			}
		}
	}
}
