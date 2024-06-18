/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:43:15 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 17:55:08 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_check_path(char *path, char *print)
{
	if (path[0] == '/')
		return (ft_check_path_check(path, print));
	else
		return (ft_check_path2(path, print));
}

char	*ft_check_path2(char *filepath, char *print)
{
	int			i;
	char		*tmp;
	char		*path;
	char		cwd[PATH_MAX];

	if (filepath[0] == '.' && filepath[1] == '/')
	{
		tmp = malloc(sizeof(char) * (ft_strlen(filepath)));
		if (!tmp)
			return (NULL);
		i = -1;
		while (filepath[++i + 1])
			tmp[i] = filepath[i + 1];
		tmp[i] = '\0';
	}
	else
		tmp = ft_strjoin("/", filepath);
	path = ft_strjoin(getcwd(cwd, sizeof(cwd)), tmp);
	free(tmp);
	return (ft_check_path_check(path, print));
}

char	*ft_check_path_check(char *path, char *print)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		free_4(path, print, NULL, NULL);
		return (NULL);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(print, 2);
		ft_putstr_fd(": is a directory\n", 2);
		free_4(path, print, NULL, NULL);
		exit(127);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(print, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(127);
	}
	else
		return (path);
}

int	ft_check_cd(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (1);
	if (!S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is not a directory\n", 2);
		return (0);
	}
	return (1);
}
