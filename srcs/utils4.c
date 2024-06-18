/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:53:43 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/11 20:27:01 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env_var_replace3(char *str, char *str2, char **my_env)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	tmp = ft_find_env_var(str2, my_env);
	if (tmp != NULL)
	{
		tmp2 = ft_strdup(str);
		free(str);
		ret = ft_strjoin(tmp2, tmp);
		free(tmp2);
		free(tmp);
		return (ret);
	}
	free(tmp);
	return (str);
}

int	ft_check_filepath(int a, char *path, t_cmd *cmd)
{
	if (a == 0)
		return (0);
	if (ft_strcmp(cmd->command, ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		free(path);
		exit(2);
	}
	else if (ft_strcmp(cmd->command, "..") == 0)
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		free(path);
		exit(127);
	}
	return (1);
}

void	ft_exit_child(t_cmd *c, char **my_env, char **args, char *str)
{
	int	code;
	int	i;

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

void	ft_handle_echo_flag(char *str, char *input, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (input[j])
	{
		if (input[j] == ' ')
			k = j + 1;
		if (input[j] != '-' && input[j] != 'n' && input[j] != ' ')
			break ;
		else if (input[j] == '-' && input[j + 1] && input[j + 1] != 'n')
			break ;
		else if (input[j] == 'n' && input[j + 1] && input[j + 1] == '-')
			break ;
		j++;
	}
	if (input[j])
		j = k;
	while (input[j])
		str[++i] = input[j++];
	i++;
	str[i] = '\0';
}
