/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:44:41 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/11 22:08:36 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return ;
}

char	**ft_env_create(char **env)
{
	int		i;
	char	**ret;

	ret = malloc(sizeof(char *) * (ft_args_size(env, 0) + 50));
	if (!ret)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		ret[i] = ft_strdup(env[i]);
		if (ret[i][0] == 'S' && ret[i][1] == 'H' && ret[i][2] == 'L'
				&& ret[i][3] == 'V' && ret[i][4] == 'L' && ret[i][5] == '=')
			ret[i] = ft_iterate_shlvl(ret[i]);
	}
	ret[i] = NULL;
	return (ret);
}

char	*ft_find_env_var(char *str, char **my_env)
{
	int		i[3];
	char	*ret;
	char	*tmp;

	i[0] = -1;
	ret = NULL;
	tmp = ft_strjoin(str, "=");
	while (my_env[++i[0]])
	{
		if (ft_strstr(my_env[i[0]], tmp))
		{
			i[1] = 0;
			while (my_env[i[0]][i[1]] && my_env[i[0]][i[1]] != '=')
				i[1]++;
			ret = malloc(sizeof(char) * (ft_strlen(my_env[i[0]]) - i[1] + 1));
			if (!ret)
				return (NULL);
			i[2] = -1;
			while (my_env[i[0]][++i[1]])
				ret[++i[2]] = my_env[i[0]][i[1]];
			ret[++i[2]] = '\0';
			return (free_3_ret_4(tmp, NULL, NULL, ret));
		}
	}
	return (free_3_ret_4(tmp, NULL, NULL, ret));
}

char	*ft_env_var_replace(char *input, char **my_env, int j)
{
	int		i[4];
	char	*str[3];

	if (!input[0])
		return (input);
	i[0] = -1;
	i[3] = j;
	str[0] = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	str[2] = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while (input[++i[0]])
	{
		if (ft_env_var_replace2(input, str[2], i) == 1)
			str[0] = ft_env_var_replace3(str[0], str[2], my_env);
		else
		{
			str[1] = ft_strdup(str[0]);
			free(str[0]);
			str[0] = ft_str_add_char(str[1], input[i[0]]);
			free(str[1]);
		}
	}
	return (free_3_ret_4(str[2], input, NULL, str[0]));
}

int	ft_env_var_replace2(char *s, char *tmp, int *i)
{
	if (s[i[0]] == '$' && s[i[0] + 1] && s[i[0] + 1] != ' ' && i[0] <= i[3])
	{
		i[1] = -1;
		i[2] = i[0];
		while (s[++i[0]] && s[i[0]] != ' ' && s[i[0]] != '$'
			&& s[i[0]] != '\"' && s[i[0]] != '\'')
			tmp[++i[1]] = s[i[0]];
		tmp[++i[1]] = '\0';
		i[0] -= 1;
		return (1);
	}
	else
		return (0);
}
