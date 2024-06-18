NAME = minishell

_SRCS = builtins_utils.c \
			builtins_utils2.c \
			builtins_utils3.c \
			builtins_utils4.c \
			builtins.c \
			builtins2.c \
			check_path.c \
			destroyers.c \
			env.c \
			errors.c \
			executable_utils.c \
			executable_utils2.c \
			executable.c \
			inspectors.c \
			lexer.c \
			main.c \
			parser_utils.c \
			parser.c \
			reader.c \
			utils_free.c \
			utils.c \
			utils2.c \
			utils3.c \
			utils4.c \

SRCS = $(addprefix srcs/, $(_SRCS))
SRCO = $(SRCS:.c=.o)

FLAG = -Wall -Wextra -Werror
INC = -I includes/

all : $(NAME)

sanitize : $(SRCO)
	make -C libft
	clang -o $(NAME) $(SRCO) libft/libft.a -lreadline -lm -fsanitize=address
	make clean

$(NAME) : $(SRCO)
	make -C libft
	clang -o $(NAME) $(SRCO) libft/libft.a -lreadline -lm

%.o : %.c
	clang $(FLAG) -o $(NAME) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO)
	make clean -C libft

fclean : clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft/libft.a

re : fclean all

rcl : re
	make clean

.PHONY: make clean fclean re rcl sanitize
