/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: requinch <requinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:48:04 by requinch          #+#    #+#             */
/*   Updated: 2022/05/12 18:00:40 by requinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_out(t_toklist *toklist, int fd)
{
	while (toklist && toklist->next)
	{
		if (toklist->type == APPEND && toklist->next->type == FILEPATH)
		{
			if (fd > 0 && fd != 1)
				close(fd);
			fd = open(toklist->next->value, O_WRONLY | O_APPEND | O_CREAT,
					S_IRWXO | S_IRWXU | S_IRWXG);
			if (fd < 0)
				return (-3);
		}
		else if (toklist->type == OUTFILE && toklist->next->type == FILEPATH)
		{
			if (fd > 0 && fd != 1)
				close(fd);
			fd = open(toklist->next->value, O_WRONLY | O_TRUNC | O_CREAT,
					S_IRWXO | S_IRWXU | S_IRWXG);
			if (fd < 0)
				return (-3);
		}
		toklist = toklist->next;
	}
	if (fd < 0 || toklist->type == APPEND || toklist->type == OUTFILE)
		return (-3);
	return (fd);
}

int	parse_in(t_toklist *toklist, int fd, char **env)
{
	while (toklist && toklist->next)
	{
		if (toklist->type == INSTDIN && toklist->next->type == FILEPATH)
			return (heredoc(toklist->next->value, env));
		else if (toklist->type == INFILE && toklist->next->type == FILEPATH)
		{
			if (fd > 0)
				close(fd);
			fd = open(toklist->next->value, O_RDONLY);
			if (fd < 0)
				return (-3);
		}
		toklist = toklist->next;
	}
	return (fd);
}

/* cmd 0 : first element
** cmd 1 : current element */

t_cmd	*parse_next(t_toklist *toklist, int infile, int outfile)
{
	int		pipefd[2];
	t_cmd	*cmd[2];

	pipefd[0] = infile;
	pipefd[1] = 1;
	toklist = next_command(toklist, 0);
	if (!toklist)
		return (NULL);
	cmd[0] = cmd_create(toklist, pipefd[0]);
	cmd[1] = cmd[0];
	while (next_command(toklist, 1))
	{
		if (check_pipe(toklist->next))
		{
			pipe(pipefd);
			cmd[1]->fd_out = pipefd[1];
		}
		toklist = next_command(toklist, 1);
		cmd[1]->next = cmd_create(toklist, pipefd[0]);
		cmd[1]->next->prev = cmd[1];
		cmd[1] = cmd[1]->next;
	}
	cmd[1]->fd_out = outfile;
	return (cmd[0]);
}

int	validate(t_toklist *toklist)
{
	int	ret;

	ret = 0;
	while (toklist)
	{
		if (toklist->type == PIPE && (!toklist->next || !toklist->prev
				|| toklist->next->type != COMMAND
				|| toklist->prev->type % 10 != 1))
			return (0);
		if ((toklist->type == APPEND || toklist->type == INSTDIN
				|| toklist->type == INFILE || toklist->type == OUTFILE)
			&& (!toklist->next || toklist->next->type % 10 != 1))
			return (0);
		ret = 1;
		toklist = toklist->next;
	}
	return (ret);
}

t_cmd	*parser(t_toklist *toklist, char **env)
{
	int			infile;
	int			outfile;
	t_cmd		*parsed;
	t_toklist	*save;

	if (!toklist)
		return (NULL);
	parsed = NULL;
	save = toklist;
	infile = 0;
	outfile = 1;
	infile = parse_in(toklist, infile, env);
	outfile = parse_out(toklist, outfile);
	if (infile == -3 || outfile == -3 || !validate(toklist))
	{
		printf("%i, %i, %i", infile, outfile, validate(toklist));
		return (destroy_toklist(toklist, NULL));
	}
	word_interpreter(toklist, toklist);
	parsed = parse_next(toklist, infile, outfile);
	return (destroy_toklist(toklist, parsed));
}
