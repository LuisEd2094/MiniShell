# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 12:40:36 by lsoto-do          #+#    #+#              #
#    Updated: 2023/05/10 17:43:32 by lsoto-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
INCLUDES		=	-I./includes
LIBFT_DIR		=	src/
PRINT_DIR		=	ftprintf/
NEXT_LINE_DIR	=	get_next_line/
OBJS_DIR		=	obj/
DEPS_DIR		=	deps/
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -f
AR				=	ar rcs


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

###

LIBFT_FILES		=	ft_atoi.c ft_isalpha.c ft_itoa.c ft_lstdelone.c ft_lstnew.c \
					ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strjoin.c \
					ft_strmapi.c ft_strtrim.c ft_bzero.c ft_isascii.c \
					ft_lstadd_back.c ft_lstiter.c ft_lstsize.c ft_memmove.c \
					ft_putnbr_fd.c ft_strcmp.c ft_strlcat.c ft_strncmp.c \
					ft_substr.c ft_calloc.c ft_isdigit.c ft_lstadd_front.c \
					ft_lstlast.c ft_memchr.c ft_memset.c ft_putstr_fd.c \
					ft_strdup.c ft_strlcpy.c ft_strnstr.c ft_tolower.c \
					ft_isalnum.c ft_isprint.c ft_lstclear.c ft_lstmap.c \
					ft_memcmp.c ft_putchar_fd.c ft_split.c ft_striteri.c ft_strlen.c\
					ft_strrchr.c ft_toupper.c ft_check_if_int.c ft_isspace.c \
					ft_remove_white_space.c check_if_white_right_left.c ft_get_sign.c \
					ft_remove_zeros.c free_2d_array.c ft_free_3d_array.c


NEXT_LINE_FILES	=	get_next_line.c get_next_line_utils.c

FTPRINTF_FILES	=	ft_c_format.c ft_i_format.c ft_printf_itoa.c ft_s_format.c \
					ft_uitoa.c ft_flags.c ft_p_format.c ft_printf_utils.c ft_safe_free.c \
					ft_x_format.c ft_flags2.c ft_printf.c ft_put_words.c ft_u_format.c



OBJS		=	$(addprefix $(OBJS_DIR), $(LIBFT_FILES:.c=.o)) \
				$(addprefix $(OBJS_DIR), $(FTPRINTF_FILES:.c=.o)) \
				$(addprefix $(OBJS_DIR), $(NEXT_LINE_FILES:.c=.o))

DEPS		=	$(addprefix $(DEPS_DIR), $(LIBFT_FILES:.c=.d)) \
				$(addprefix $(DEPS_DIR), $(FTPRINTF_FILES:.c=.d)) \
				$(addprefix $(DEPS_DIR), $(NEXT_LINE_FILES:.c=.d))

###


all:	$(NAME) 

$(OBJS_DIR)%.o: $(LIBFT_DIR)%.c | $(OBJS_DIR) $(DEPS_DIR)
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
			@mv $(OBJS_DIR)$(notdir $(basename $<)).d $(DEPS_DIR)


$(OBJS_DIR)%.o: $(PRINT_DIR)%.c | $(OBJS_DIR) $(DEPS_DIR)
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
			@mv $(OBJS_DIR)$(notdir $(basename $<)).d $(DEPS_DIR)

$(OBJS_DIR)%.o: $(NEXT_LINE_DIR)%.c | $(OBJS_DIR) $(DEPS_DIR)
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
			@mv $(OBJS_DIR)$(notdir $(basename $<)).d $(DEPS_DIR)
			 
$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@ranlib $(NAME)
			@echo "$(GREEN)Libft compiled! $(DEF_COLOR)"

$(OBJS_DIR):
		@echo "$(GREEN)Creating Obj Dir $(DEF_COLOR)"
		@mkdir -p $(OBJS_DIR)
$(DEPS_DIR):
		@echo "$(GREEN)Creating Deps Dir $(DEF_COLOR)"
		@mkdir -p $(DEPS_DIR)


-include $(DEPS)

clean:
		@$(RM) -rf $(OBJS_DIR) $(DEPS_DIR)
		@echo "$(GREEN)Libft objects and Deps cleaned!$(DEF_COLOR)"

fclean:	clean
		@$(RM) -f $(NAME)
		@echo "$(GREEN)Libft library cleaned!$(DEF_COLOR)"

re:		fclean all
		@echo "$(GREEN)Cleaned and rebuilt everything!$(DEF_COLOR)"


.PHONY:		all clean fclean re
