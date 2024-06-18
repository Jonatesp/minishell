/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:14:32 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 16:02:42 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *str)
{
	char	c;
	int		i;

	i = -1;
	c = str[0];
	while (str[++i])
	{
		if (i && str[i] == c)
			return (i);
	}
	return (0);
}

char	*cut_element(char *str)
{
	char	*cut;
	int		i;
	int		c;

	i = 0;
	while (str[i] && str[i] != 32)
	{
		if (((str[i] == 34 || str[i] == 39) && check_quotes(&str[i]))
			|| str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if (i == 0)
			{
				c = str[i];
				i++;
				while (str[i] != c && (c == 34 || c == 39))
					i++;
				i += (str[i] == 34 || str[i] == 39);
				i += (str[i] && str[i] == c && (c == '<' || c == '>'));
			}
			break ;
		}
		i++;
	}
	cut = ft_substr(str, 0, i);
	return (cut);
}

t_split	*split_mk2(char *str)
{
	t_split	*split;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = 0;
	split = ft_calloc(1, sizeof(t_split));
	split->spaces = ft_calloc(120, sizeof(int));
	split->args = ft_calloc(120, sizeof(char *));
	while (str[++i[0]])
	{
		if (str[i[0]] != ' ')
		{
			split->args[++i[1]] = cut_element(&str[i[0]]);
			split->spaces[i[1]] = i[2];
			i[0] += (ft_strlen(split->args[i[1]]) - 1);
		}
		i[2] = (str[i[0]] == ' ');
	}
	split->args[++i[1]] = NULL;
	if (i[1] == 0)
		split->args[i[1]] = ft_strdup(str);
	split->spaces[i[1]] = -1;
	return (split);
}

t_split	*ft_reader(char **env)
{
	char	*str;
	char	*prompt;
	t_split	*ret;
	char	cwd[PATH_MAX];
	int		i;

	prompt = ft_strjoin(getcwd(cwd, sizeof(cwd)), "$> ");
	rl_catch_signals = 0;
	str = readline(prompt);
	if (str == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		i = -1;
		while (env[++i])
			free(env[i]);
		free(env);
		free(prompt);
		exit (g_rvalue);
	}
	if (!str[0])
		return (free_3_ret_4(prompt, str, NULL, NULL));
	add_history(str);
	ret = split_mk2(str);
	return (free_3_ret_4(str, prompt, NULL, ret));
}
