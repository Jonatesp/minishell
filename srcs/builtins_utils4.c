/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:33:33 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 18:21:43 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_cd2(char *input, char **env, t_cmd *c)
{
	int		ret;
	char	**env_cpy;
	char	**env_cpy2;

	if (c->arg[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (free_1_ret_2(input, env));
	}
	env_cpy = ft_set_env_oldpwd(env);
	ret = chdir(input);
	env_cpy2 = ft_set_env_pwd(env_cpy);
	ft_free_args(NULL, env_cpy);
	if (ret == -1)
	{
		if (ft_check_cd(input))
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(input, 2);
			ft_putstr_fd("\n", 2);
			g_rvalue = 1;
		}
	}	
	ft_free_args(input, env);
	return (env_cpy2);
}

char	**ft_set_env_oldpwd(char **env)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];
	char	**env_cpy;

	ret = ft_strdup("OLDPWD");
	tmp = ft_find_env_var(ret, env);
	free(ret);
	if (tmp)
	{
		free(tmp);
		tmp = ft_strdup("OLDPWD=");
		ret = ft_strjoin(tmp, getcwd(cwd, sizeof(cwd)));
		free(tmp);
		env_cpy = ft_export_replace(ret, env);
		free(ret);
		return (env_cpy);
	}
	return (ft_env_copy(env));
}

char	**ft_set_env_pwd(char **env)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];
	char	**env_cpy;

	if (ft_check_env_var("PWD", env))
	{
		tmp = ft_strdup("PWD=");
		ret = ft_strjoin(tmp, getcwd(cwd, sizeof(cwd)));
		free(tmp);
		env_cpy = ft_export_replace(ret, env);
		free(ret);
		return (env_cpy);
	}
	return (ft_env_copy(env));
}

int	ft_check_env_var(char *str, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && str[j] && env[i][j] == str[j])
		{
			j++;
			if ((env[i][j] == '=' && !str[j]) || (!str[j] && !env[i][j]))
				return (1);
		}
	}
	return (0);
}
