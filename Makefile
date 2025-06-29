# THIS FILE IS FOR MACOS PLEASE USE ANOTHER MAKEFILE IF UBUNTU

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -Iincludes -I/opt/homebrew/opt/readline/include
LDFLAGS := -L/opt/homebrew/opt/readline/lib -lreadline
RM := rm -rf

# Directory structure
MAIN_DIR := main
PARSE_DIR := parse
EXECUTE_DIR := execute
OBJ_DIR := obj
LIBFT := libft/libft.a
LIBFT_OBJ := libft/obj

# Source files
MAIN_SRCS := main.c
PARSE_SRCS := parse.c token.c checks.c helpers.c lexer.c tokenizer.c extract.c helpers1.c cmd.c convert.c assign_cmd.c expansions.c
EXECUTE_SRCS := cmd_exit.c lstfnc.c startshell.c cmd_export_env.c pipe_utils.c utils.c builtin.c cmd_unset.c start_exe.c utils2.c heredoc.c ft_free.c

# Add directory prefixes
MAIN_SRCS := $(addprefix $(MAIN_DIR)/, $(MAIN_SRCS))
PARSE_SRCS := $(addprefix $(PARSE_DIR)/, $(PARSE_SRCS))
EXECUTE_SRCS := $(addprefix $(EXECUTE_DIR)/, $(EXECUTE_SRCS))
SRCS := $(MAIN_SRCS) $(PARSE_SRCS) $(EXECUTE_SRCS)

# Object files
OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXECUTE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(LIBFT_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
