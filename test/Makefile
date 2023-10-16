NAME = mytest

LIB_DIR = /home/luised2094/MiniShell/Libft

#LIB_FILES := $(wildcard $(LIB_DIR)/**/*.c)
LIB_FILES := $(wildcard ../Libft/**/*.c)


SRC_FILES = mytest.c unity.c ../check_valid_identifier.c
#LIB_FLAGS = -I./ -I$(LIB_DIR)/includes
LIB_FLAGS = -I./ -I../includes

all: $(NAME)

$(NAME): $(SRC_FILES)
	@gcc $(LIB_FILES) $(SRC_FILES) $(LIB_FLAGS) -o $(NAME)


fclean: 
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"



re: fclean all 