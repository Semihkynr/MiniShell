NAME = minishell

SRCS =	./src/main.c ./src/startshell.c ./src/utils/utils.c ./src/utils/utils2.c ./src/utils/lstfnc.c ./src/builtin/builtin.c ./src/builtin/cmd_export_env.c 

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline 

CHECK_READLINE = dpkg -s libreadline-dev >/dev/null 2>&1 || sudo apt-get install -y libreadline-dev

all: check_readline $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

check_readline:
	@$(CHECK_READLINE)

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re check_readline
