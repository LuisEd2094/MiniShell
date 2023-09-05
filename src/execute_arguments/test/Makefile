NAME = mytest

LIB_DIR = /home/luised2094/MiniShell/Libft

LIB_FILES := $(wildcard $(LIB_DIR)/**/*.c)

SRC_FILES = ../get_cmd_value.c ../skips.c unity.c mytest.c

LIB_FLAGS = -I./ -I../ -I$(LIB_DIR)/includes -I/home/luised2094/MiniShell/includes

all: $(NAME)

$(NAME): $(SRC_FILES)
	@gcc $(LIB_FILES) $(SRC_FILES) $(LIB_FLAGS) -o $(NAME)


fclean: 
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"



re: fclean all 