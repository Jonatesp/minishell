/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:52:56 by requinch          #+#    #+#             */
/*   Updated: 2022/05/12 18:06:37 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_last_return(char *input, int j)
{
	int		i[2];
	char	*tmp;
	char	*ret;
	char	*res;

	tmp = malloc(sizeof(char) * ft_strlen(input));
	if (!tmp)
		return (NULL);
	i[0] = -1;
	while (++i[0] < j)
		tmp[i[0]] = input[i[0]];
	tmp[i[0]] = '\0';
	ret = ft_itoa(g_rvalue);
	res = ft_strjoin(tmp, ret);
	free(ret);
	i[1] = i[0] + 1;
	i[0] = -1;
	while (input[++i[1]])
		tmp[++i[0]] = input[i[1]];
	if (!input[i[1]])
		i[0]++;
	tmp[i[0]] = '\0';
	ret = ft_strjoin(res, tmp);
	free_4(res, tmp, input, NULL);
	return (ret);
}

int	ft_args_size(char **input, int i)
{
	while (input[i])
		i++;
	return (i);
}

char	*ft_fp(char **args)
{
	if (!args)
		return (NULL);
	return (ft_strcpy(args[0]));
}

void	ft_close_fds(t_cmd *cmd, int type)
{
	t_cmd	*cmd2;

	cmd2 = cmd;
	while (cmd2->prev)
		cmd2 = cmd2->prev;
	if (type == 0)
	{
		if (cmd->fd_in != STDIN_FILENO)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out != STDOUT_FILENO)
			dup2(cmd->fd_out, STDOUT_FILENO);
	}
	while (cmd2)
	{
		if (cmd2->fd_out != STDOUT_FILENO)
			close(cmd2->fd_out);
		if (cmd2->fd_in != STDIN_FILENO)
			close(cmd2->fd_in);
		cmd2 = cmd2->next;
	}
}

char	*ft_str_add_char(char *str, char c)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	ret[i] = c;
	ret[i + 1] = '\0';
	return (ret);
}
