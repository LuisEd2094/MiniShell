NAME        = minishell
CFLAGS      = -g ##-Wall -Wextra  -Werror -g
RM          = rm -f
SRCS_PATH           = src/
OBJS_PATH           = obj/
HISTORY_PATH			= history/
MAKE_OBJ_DIR		= $(OBJS_PATH) $(addprefix $(OBJS_PATH), $(HISTORY_PATH))
DEPS_PATH	= deps/
LIB_PATH	= 	./Libft
LIB			=	$(LIB_PATH)/libft.a
LDFLAGS		= 	-L$(LIB_PATH) -lft
LINEFLAGS	=	-lreadline

INCS        = -I./includes/

#Colors


DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
LIGHT_GREEN = \033[1;92m

###

SRC         =	main.c 

HISTORY		= 	add_to_history.c  close_history.c  history_init.c  \
				remove_new_line.c  update_history.c work_history.c
				


HISTORY_FILES	=	$(addprefix $(HISTORY_PATH), $(HISTORY))


DEPS		= 	$(addprefix $(DEPS_PATH), $(SRC:.c=.d) $(HISTORY:.c=.d))

SRC			+=	$(HISTORY_FILES)

OBJS        =	$(addprefix $(OBJS_PATH), $(SRC:.c=.o)) 
				

all: make_lib $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(MAKE_OBJ_DIR) $(DEPS_PATH)
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o  $@
			@mv $(basename $@).d $(DEPS_PATH)


$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LINEFLAGS) -o $(NAME) $(LDFLAGS)
	@echo "$(LIGHT_GREEN)Created $(NAME) executable$(DEF_COLOR)"

make_lib:
	@echo "$(GREEN)Checking Libft$(DEF_COLOR)"
	@$(MAKE) -s -C $(LIB_PATH)
	@echo "$(BLUE)Done checking Libft$(DEF_COLOR)"


$(MAKE_OBJ_DIR):
	@echo "$(GREEN)Creating $(NAME) Obj Dir $(DEF_COLOR)"
	@mkdir -p $(MAKE_OBJ_DIR)

$(DEPS_PATH):
	@echo "$(GREEN)Creating $(NAME) Deps Dir $(DEF_COLOR)"
	@mkdir -p $(DEPS_PATH)

-include $(DEPS)

fclean_lib:
	@$(MAKE) fclean -s -C $(LIB_PATH)

clean_lib:
	@$(MAKE) clean -s -C $(LIB_PATH) 


clean: clean_lib clean_objects

fclean:  clean_objects fclean_lib
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"

clean_objects:
	@echo "$(GREEN)$(NAME) Objects and Dependencies cleaned!$(DEF_COLOR)"
	@$(RM) -r $(OBJS_PATH) $(DEPS_PATH)


re: fclean all 

.PHONY: all fclean clean re 