NAME = mytest

LIB_DIR = /home/luised2094/MiniShell/Libft

SRC_DIR = /home/luised2094/MiniShell/src

LIB_FILES := $(wildcard $(LIB_DIR)/**/*.c)


SRC_FILES = ../get_cmd_value.c ../get_double_quote.c ../move_start_and_argument_len.c ../get_cmd_argument.c  ../../builtins/env/env.c unity.c mytest.c \
			../../mini_shared/*.c

LIB_FLAGS = -I./ -I../ -I$(LIB_DIR)/includes -I/home/luised2094/MiniShell/includes

all: $(NAME)

$(NAME): $(SRC_FILES)
	@gcc $(LIB_FILES) $(SRC_FILES) $(LIB_FLAGS) -o $(NAME)


fclean: 
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"



re: fclean all 