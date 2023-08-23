NAME        = minishell
CFLAGS      = -g ##-Wall -Wextra  -Werror -g
RM          = rm -f
SRCS_PATH           = src/
OBJS_PATH           = obj/
HISTORY_PATH		= history/
BUILTINTS			= builtins/
EXECUTE_PATH		= execute_arguments/
ERROR_PATH			= print_error/
EXPORT_PATH			= $(BUILTINTS)export/
ENV_PATH			= $(BUILTINTS)env/
SHARED_PATH			= $(BUILTINTS)shared/
UNSET_PATH			= $(BUILTINTS)unset/
BUILTINTS_PATH		= $(EXPORT_PATH) $(ENV_PATH) $(SHARED_PATH) $(UNSET_PATH)

## Add new path, just need name/
MAKE_OBJ_DIR		= $(OBJS_PATH) $(addprefix $(OBJS_PATH), \
											$(HISTORY_PATH) \
											$(BUILTINTS_PATH) \
											$(EXECUTE_PATH) \
											$(ERROR_PATH) \
											) 
										
#Add new path to objects

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

EXPORT		=	export.c bts_for_export.c

ENV			= 	env.c

UNSET		=	unset.c

SHARED		=	builtins_shared.c ft_single_split.c

EXECUTE		=	execute_arguments.c get_cmd_value.c skips.c \
				handle_redirections.c aux_handle_redirections.c

ERROR		=	print_error.c

## Add names of your files

HISTORY_FILES		=$(addprefix $(HISTORY_PATH), $(HISTORY))

EXECUTE_FILES			=$(addprefix $(EXECUTE_PATH), $(EXECUTE))

ERROR_FILES			=$(addprefix $(ERROR_PATH), $(ERROR))

EXPORT_FILES		=$(addprefix $(EXPORT_PATH), $(EXPORT))
ENV_FILES			=$(addprefix $(ENV_PATH), $(ENV))
SHARED_BINS_FILES	=$(addprefix $(SHARED_PATH), $(SHARED))
UNSET_FILES			=$(addprefix $(UNSET_PATH), $(UNSET))

BUILTINTS_FILES		=$(EXPORT_FILES) $(ENV_FILES) $(SHARED_BINS_FILES) $(UNSET_FILES)
## append the path to your files

DEPS		= 	$(addprefix $(DEPS_PATH), $(SRC:.c=.d) \
										$(HISTORY:.c=.d) \
										$(BUILTINTS_FILES:.c=.d) \
										$(EXECUTE_FILES:.c=.d)) \
										$(ERROR_FILES:.c=.d)

#add .d files to deps

SRC			+=	$(HISTORY_FILES) $(BUILTINTS_FILES) $(EXECUTE_FILES) $(ERROR_FILES)

## add to sercs

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