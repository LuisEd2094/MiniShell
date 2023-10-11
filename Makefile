NAME        = minishell
CFLAGS      = -g #-Wall -Wextra  -Werror
RM          = rm -f
SRCS_PATH           = src/
OBJS_PATH           = obj/
HISTORY_PATH			= history/
EXECVE_PATH			= execve/

#BUILT INS variables
PIPE_PATH			= pipe/
BUILTINTS			= builtins/
ARGUMENTS_PATH		= get_arguments/
EXEC_CMDS_PATH		= execute_cmds/
SIGNALS_PATH		= signals/
REDIR_PATH			= redirections/
EXPORT_PATH			= $(BUILTINTS)export/
ENV_PATH			= $(BUILTINTS)env/
UNSET_PATH			= $(BUILTINTS)unset/
CD_PATH				= $(BUILTINTS)cd/
ECHO_PATH			= $(BUILTINTS)echo/
PWD_PATH			= $(BUILTINTS)pwd/
BUILTINTS_PATH		= $(EXPORT_PATH) $(ENV_PATH) $(UNSET_PATH) $(CD_PATH) $(ECHO_PATH) $(PWD_PATH)
MINI_SHARED_PATH	= mini_shared/
SIGNALS_PATH		= signals/
PARSE_INPUT_PATH	= parse_input/


## Add new path, just need name/
MAKE_OBJ_DIR		= $(OBJS_PATH) $(addprefix $(OBJS_PATH), \
											$(HISTORY_PATH) \
											$(BUILTINTS_PATH) \
											$(ARGUMENTS_PATH) \
											$(EXECVE_PATH)\
											$(EXEC_CMDS_PATH) \
											$(MINI_SHARED_PATH) \
											$(REDIR_PATH) \
											$(SIGNALS_PATH) \
											$(PIPE_PATH) \
											$(PARSE_INPUT_PATH) \
											) 
										
#Add new path to objects

DEPS_PATH	= deps/
LIB_PATH	= 	./Libft
LIB			=	$(LIB_PATH)/libft.a #./readline/libreadline.a ./readline/libhistory.a
LDFLAGS		= 	-L$(LIB_PATH) -lft 
LINEFLAGS	=	-lreadline

INCS        = -I./includes/ \
-I./readline/ 

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

SRC         =	main.c main_aux.c

HISTORY		= 	add_to_history.c  close_history.c  history_init.c  \
				remove_new_line.c  update_history.c work_history.c

EXPORT		=	export.c bts_for_export.c

ENV			= 	env.c

UNSET		=	unset.c

CD			=	ft_cd.c

ECHO		=	ft_echo.c

PWD			=	ft_pwd.c

ARGUMENTS	=	get_cmd_value.c get_cmd_argument.c 

EXEC_CMDS	=	execute_cmds.c check_quotes_and_env.c get_double_quote.c

EXECVE		=	execve.c execve_aux.c


MINI_SHARED	=	get_next_word_and_len.c is_ascii_no_space.c skips.c \
				builtins_shared.c ft_single_split.c get_env_value_str.c \
				replace_env.c create_or_update_env_node.c \
				print_error.c free_node.c


REDIRECTIONS	= aux_handle_redirections.c  handle_redirections.c  here_doc.c

SIGNALS		=	signals.c

PIPE 		=	memory_pipe.c  pipe.c


PARSE_INPUT =	parse_input.c


## Add names of your files

HISTORY_FILES		=$(addprefix $(HISTORY_PATH), $(HISTORY))

ARGUMENTS_FILES			=$(addprefix $(ARGUMENTS_PATH), $(ARGUMENTS))

EXPORT_FILES		=$(addprefix $(EXPORT_PATH), $(EXPORT))
ENV_FILES			=$(addprefix $(ENV_PATH), $(ENV))
UNSET_FILES			=$(addprefix $(UNSET_PATH), $(UNSET))
PWD_FILES			=$(addprefix $(PWD_PATH), $(PWD))
CD_FILES			=$(addprefix $(CD_PATH), $(CD))
ECHO_FILES			=$(addprefix $(ECHO_PATH), $(ECHO))

BUILTINTS_FILES		=$(EXPORT_FILES) $(ENV_FILES) $(UNSET_FILES) $(PWD_FILES) $(CD_FILES) $(ECHO_FILES)

EXECVE_FILES		=$(addprefix $(EXECVE_PATH), $(EXECVE))

EXEC_CMDS_FILE		= $(addprefix $(EXEC_CMDS_PATH), $(EXEC_CMDS))

MINI_SHARED_FILES	= $(addprefix $(MINI_SHARED_PATH), $(MINI_SHARED))

REDIR_FILES			= $(addprefix $(REDIR_PATH), $(REDIRECTIONS))

SIGNALS_FILES		= $(addprefix $(SIGNALS_PATH), $(SIGNALS))

PIPE_FILES			= $(addprefix $(PIPE_PATH), $(PIPE))

PARSE_INPUT_FILES	= $(addprefix $(PARSE_INPUT_PATH), $(PARSE_INPUT))

## append the path to your files

DEPS		= 	$(addprefix $(DEPS_PATH), $(SRC:.c=.d) \
										$(HISTORY:.c=.d) \
										$(BUILTINTS_FILES:.c=.d) \
										$(ARGUMENTS_FILES:.c=.d) \
										$(EXECVE_FILES:.c=.d) \
										$(EXEC_CMDS_FILE:.c=.d) \
										$(MINI_SHARED_FILES:.c=.d) \
										$(REDIR_FILES:.c=.d) \
										$(SIGNALS_FILES:.c=.d) \
										$(PIPE_FILES:.c=.d)\
										$(PARSE_INPUT_FILES:.c=.d)\
										) 
										
										

#add .d files to deps

SRC			+=	$(HISTORY_FILES) $(BUILTINTS_FILES) $(ARGUMENTS_FILES) \
				$(EXECVE_FILES) $(EXEC_CMDS_FILE) $(PARSE_FILES) $(MINI_SHARED_FILES) \
				$(REDIR_FILES) $(SIGNALS_FILES) $(PIPE_FILES) $(PARSE_INPUT_FILES)

## add to sercs

OBJS        =	$(addprefix $(OBJS_PATH), $(SRC:.c=.o)) 
				

all: conf make_lib $(NAME)

conf:
	@if [ ! -f $(READL)config.status ]; then\
		cd $(READL) && ./configure &> /dev/null; \
		echo "✅ ==== $(G)$(ligth)Create config.status$(E)==== ✅"; \
	fi

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(MAKE_OBJ_DIR) $(DEPS_PATH)
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCS) -MMD -MP -c -D READLINE_LIBRARY=1 $< -o  $@
			@mv $(basename $@).d $(DEPS_PATH)


$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LINEFLAGS) $(LIB) -ltermcap -o $(NAME) $(LDFLAGS)
	@echo "$(LIGHT_GREEN)Created $(NAME) executable$(DEF_COLOR)"

make_lib:
	make -C ./readline/ --no-print-directory &> /dev/null
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
