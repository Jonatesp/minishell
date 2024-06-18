/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 18:55:31 by requinch          #+#    #+#             */
/*   Updated: 2022/05/12 18:09:07 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(char *delimiter, char **env)
{
	int		fd;
	int		gnlret;
	char	*line;
	char	*sec;

	gnlret = 0;
	fd = open(".heredoc", O_WRONLY | O_APPEND | O_CREAT,
			S_IRWXO | S_IRWXU | S_IRWXG);
	while (gnlret > -1)
	{
		write(STDOUT_FILENO, "> ", 2);
		gnlret = get_next_line(STDIN_FILENO, &line);
		if (gnlret == -1)
			return (-3);
		if (!ft_strcmp(line, delimiter))
			return (heredoc_part_2(fd, line));
		sec = ft_path_gev(line, env);
		write(fd, sec, ft_strlen(sec));
		write(fd, "\n", 1);
		free_4(line, sec, NULL, NULL);
	}
	return (-3);
}

t_toklist	*next_command(t_toklist *toklist, int num)
{
	while (toklist && toklist->type != COMMAND)
		toklist = toklist->next;
	if (!toklist)
		return (NULL);
	if (num == 1)
		return (next_command(toklist->next, 0));
	else
		return (toklist);
}

int	check_pipe(t_toklist *toklist)
{
	while (toklist)
	{
		if (toklist->type == PIPE)
			return (1);
		toklist = toklist->next;
	}
	return (0);
}

t_cmd	*cmd_create(t_toklist *toklist, int pipefd_in)
{
	int		i;
	t_cmd	*new;

	i = -1;
	new = malloc(sizeof(t_cmd));
	new->command = ft_strdup(toklist->value);
	new->fd_in = pipefd_in;
	new->fd_out = 1;
	new->next = NULL;
	new->prev = NULL;
	new->arg = NULL;
	new->spaces = duplicate_spaces(toklist->spaces, 0, 0);
	toklist = toklist->next;
		new->arg = ft_calloc((1 + 49 * (!(!toklist))), sizeof(char *));
	while (toklist && (toklist->type % 10) == 1)
	{
		new->arg[++i] = ft_strdup(toklist->value);
		toklist = toklist->next;
	}
	new->arg[++i] = NULL;
	return (new);
}

t_toklist	*word_interpreter(t_toklist *toklist, t_toklist *save)
{
	enum e_token	prev;

	if (toklist && toklist->prev == NULL)
	{
		if (toklist->type == WORD)
			toklist->type = COMMAND;
		toklist = toklist->next;
	}
	while (toklist && toklist->prev)
	{
		if (toklist->type == WORD)
		{
			prev = toklist->prev->type;
			if (prev == PIPE || prev == FILEPATH)
			{
				toklist->type = COMMAND;
			}
			else if (prev == 3 || prev == 5 || prev == 6 || prev == 4)
				toklist->type = FILEPATH;
			else if (prev == COMMAND || prev == ARGUMENT)
				toklist->type = ARGUMENT;
		}
		toklist = toklist->next;
	}
	return (save);
}
