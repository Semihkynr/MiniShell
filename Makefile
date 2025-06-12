# Name and compiler
NAME := minishell
CC := cc

# Flags
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -lreadline

# Directories
MAIN_DIR := main
SRC_DIR := src
PARSE_DIR := parse
LIBFT_DIR := libft
OBJ_DIR := obj

# Source files
MAIN_SRCS := $(MAIN_DIR)/main.c
SRCS := $(shell find $(SRC_DIR) -name "*.c")
PARSE_SRCS := $(shell find $(PARSE_DIR) -name "*.c")
LIBFT_SRCS := $(shell find $(LIBFT_DIR)/core -name "*.c")
ALL_SRCS := $(MAIN_SRCS) $(SRCS) $(PARSE_SRCS) $(LIBFT_SRCS)

# Object files
MAIN_OBJS := $(patsubst $(MAIN_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
PARSE_OBJS := $(patsubst $(PARSE_DIR)/%.c, $(OBJ_DIR)/%.o, $(PARSE_SRCS))
LIBFT_OBJS := $(patsubst $(LIBFT_DIR)/core/%.c, $(OBJ_DIR)/%.o, $(LIBFT_SRCS))
ALL_OBJS := $(MAIN_OBJS) $(OBJS) $(PARSE_OBJS) $(LIBFT_OBJS)

# Targets
all: $(NAME)

$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LDFLAGS) -o $(NAME)

# Compile rules
$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/core/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re