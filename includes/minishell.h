/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:40:12 by anbourge          #+#    #+#             */
/*   Updated: 2022/05/12 18:16:04 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <limits.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

extern int	g_rvalue;

enum	e_token
{
	INVALID = 0,
	WORD = 1,
	COMMAND = 11,
	ARGUMENT = 21,
	FILEPATH = 31,
	PIPE = 2,
	INFILE = 3,
	INSTDIN = 4,
	OUTFILE = 5,
	APPEND = 6,
};

typedef struct s_split
{
	char	**args;
	int		*spaces;
}				t_split;

typedef struct s_toklist
{
	enum e_token		type;
	char				*value;
	int					*spaces;
	struct s_toklist	*next;
	struct s_toklist	*prev;
}				t_toklist;

/* builtins_utils.c */
void			ft_echo2(char *input, char *str, int flag, int i);
char			**ft_export2(char *input, char **my_env);
char			**ft_unset2(char **input, int i, int j, char **my_env);
void			ft_print_env_alpha(char **my_env);
void			ft_print_env_alpha2(int len, char **tmp);

/* builtins_utils2.c */
int				ft_exit2(char *arg, int code);
int				ft_exit3(char **args, int i);
char			*ft_remove_dollar(char *str, int j);
int				ft_export3(char *str, char *tmp);
char			**ft_realloc_env(char **env, char *tmp);

/* builtins_utils3.c */
void			ft_echo3(char *str, int flag);
void			ft_print_env_alpha3(char **tmp);
void			ft_print_env_alpha4(char **tmp, int *i);
char			*ft_getenv(char *str, char **env);
char			*ft_getenv2(char **env, int i, int j);

/* builtins_utils4.c */
char			**ft_cd2(char *input, char **env, t_cmd *c);
char			**ft_set_env_oldpwd(char **env);
char			**ft_set_env_pwd(char **env);
int				ft_check_env_var(char *str, char **env);

/* builtins.c */
int				ft_find_builtins(t_cmd *cmd);
char			**ft_cd(char *input, char **env, char **args, t_cmd *c);
void			ft_echo(char *input);
void			ft_pwd(int fd);
void			ft_exit(t_cmd *cmd, char **my_env, char **args, char *str);

/* builtins2.c */
char			**ft_export(char **input, char **my_env);
char			**ft_unset(char **input, char **my_env);
char			**ft_export_replace(char *input, char **my_env);
char			**ft_export_replace2(char **my_env,
					char *tmp, char *input, int *i);
int				ft_check_export_unset_input(char *str);

/* check_path.c */
char			*ft_check_path(char *path, char *print);
char			*ft_check_path2(char *filepath, char *print);
char			*ft_check_path_check(char *path, char *print);
int				ft_check_cd(char *input);

/* destroyers.c */
t_cmd			*destroy_toklist(t_toklist *toklist, t_cmd *parsed);
t_toklist		*destroy_split(t_split *split, t_toklist *toklist);
void			destroy_cmd(t_cmd *cmd);
void			ft_destroyer(t_cmd *c, char **my_env, char **args, char *str);

/* env.c */
void			ft_env(char **env);
char			**ft_env_create(char **env);
char			*ft_find_env_var(char *tmp, char **my_env);
char			*ft_env_var_replace(char *input, char **my_env, int j);
int				ft_env_var_replace2(char *input, char *tmp, int *i);

/* errors.c */
void			ft_exec_errors(char **args,
					t_cmd *c, char **env, int type);

/* executable_utils.c */
void			gev(char **args, char **my_env);
void			gev2(char **args, int i, int *q, char **my_env);
char			*ft_remove_quotes(char *str);
int				check_quotes_gev(char *str, int j);
char			**ft_get_arg(t_cmd *cmd, char **args);

/* executable_utils2.c */
char			*ft_get_path(char *arg, int pos, char *var_path);
char			*ft_get_path2(char *tmp, char *arg);
char			**ft_exec_builtins(t_cmd *cmd, char **env,
					char *str, char **args);
void			ft_exec_builtins_childs(t_cmd *cmd, char **env,
					char *str, char **args);
char			*ft_path_gev(char *path, char **env);

/* executable.c */
char			**builtin_alone_routine(t_cmd *cmds, char **env);
void			children_subroutine(t_cmd *c, char *filepath, char **env);
pid_t			*procreate(t_cmd *cmds, char *filepath, char **env);
char			**ft_executable(t_cmd *cmds, char *filepath, char **env);
char			*ft_executable2(char *filepath, t_cmd *c, int a, char **env);

/* inspectors.c */
void			coloscopy(char *str);
void			inspecteur_poirot(t_cmd *cmd);
void			inspecteur_gadget(t_toklist *toklist);

/* lexer.c */
enum e_token	what_is_this_shit(char *shit);
t_toklist		*lexer(t_split *read);
t_toklist		*lexer_1(t_split *read, t_toklist *prev, int i);
int				*duplicate_spaces(int *spaces, int start, int size);

/* parser_utils.c */
int				heredoc(char *delimiter, char **env);
t_toklist		*next_command(t_toklist *toklist, int num);
t_cmd			*cmd_create(t_toklist *toklist, int pipefd_in);
int				check_pipe(t_toklist *toklist);
t_toklist		*word_interpreter(t_toklist *toklist, t_toklist *save);

/* parser.c */
int				parse_out(t_toklist *toklist, int fd);
int				parse_in(t_toklist *toklist, int fd, char **env);
t_cmd			*parse_next(t_toklist *toklist, int infile, int outfile);
int				validate(t_toklist *toklist);
t_cmd			*parser(t_toklist *toklist, char **env);

/* reader.c */
int				check_quotes(char *str);
char			*cut_element(char *str);
t_split			*split_mk2(char *str);
t_split			*ft_reader(char **env);

/* utils_free.c */
void			*free_3_ret_4(void *first,
					void *second, void *third, void *fourth);
void			free_4(void	*first, void *second, void *third, void *fourth);
void			ft_free_args(char *str, char **args);
char			**free_1_ret_2(void *first, char **second);

/* utils.c */
char			*ft_last_return(char *input, int j);
int				ft_args_size(char **input, int i);
char			*ft_fp(char **args);
void			ft_close_fds(t_cmd *cmd, int type);
char			*ft_str_add_char(char *str, char c);

/* utils2.c */
int				heredoc_part_2(int fd, char *line);
int				cnt_sp(int *spaces);
char			**ft_copy_args(t_cmd *cmd);
char			**ft_main_util(t_cmd *cmd, char **my_env);

/* utils3.c */
char			**ft_args_copy(t_cmd *cmd, char **env);
char			*ft_iterate_shlvl(char *str);
char			**ft_env_copy(char **env);
int				ft_check_env(char *str, char *tmp);
void			ft_handler_c2(char *prompt, char *spaces, char *tmp);

/* utils4.c */
char			*ft_env_var_replace3(char *str, char *str2, char **my_env);
int				ft_check_filepath(int a, char *path, t_cmd *cmd);
void			ft_exit_child(t_cmd *c, char **my_env, char **args, char *str);
void			ft_handle_echo_flag(char *str, char *input, int i);

#endif