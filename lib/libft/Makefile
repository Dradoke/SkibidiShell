# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/21 21:42:42 by mavander          #+#    #+#              #
#    Updated: 2025/08/13 19:17:32 by ngaudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME			=	libft.a

# Compiler Settings
CC				=	gcc
CFLAG			=	-Wall -Wextra -Werror -g3

# Directories
SRC_DIR			=	src/
OBJ_DIR			=	obj/
LIB_DIR			=	lib/
INC_DIR			=	include/ get_next_line/ ft_printfd/

# Library Paths
LIBFT_DIR		=	$(LIB_DIR)libft/

# Source Files
SRC				=	$(LIBFT_SRC) $(GNL_SRC) $(PRINTF_SRC) $(CUSTOM_SRC)

# Object Files
OBJ				=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))

# Include & Library Flags
IFLAG			=	$(addprefix -I, $(INC_DIR))
LFLAG			=	$(addprefix -L, )
LIB				=	

# Source Files List
CUSTOM_DIR		=	custom/
CUSTOM_SRC		=	$(addprefix $(CUSTOM_DIR)/, \
					ft_abs.c \
					ft_atoi_base.c \
					ft_atol.c \
					ft_degtorad.c \
					ft_isspace.c \
					ft_radtodeg.c \
					ft_rand_str.c \
					ft_realloc.c \
					ft_strcmp.c \
					ft_strcpy.c \
					ft_strjoin_free.c \
					ft_vfree.c \
					)

PRINTF_DIR		=	ft_printfd/
PRINTF_SRC		=	$(addprefix $(PRINTF_DIR)/, \
					ft_printfd_cspct.c \
					ft_printfd.c \
					ft_putnbr_base.c \
					)

GNL_DIR			=	get_next_line/
GNL_SRC			=	$(addprefix $(GNL_DIR)/, \
					get_next_line_utils.c \
					get_next_line.c \
					)

LIBFT_DIR		=	libft/
LIBFT_SRC		=	$(addprefix $(LIBFT_DIR)/, \
					ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_strlen.c \
					ft_memset.c \
					ft_bzero.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_strlcpy.c \
					ft_strlcat.c \
					ft_toupper.c \
					ft_tolower.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strncmp.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_strnstr.c \
					ft_atoi.c \
					ft_calloc.c \
					ft_strdup.c \
					ft_substr.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_split.c \
					ft_itoa.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \
					)

# Main Target
$(NAME):	$(OBJ)
	@ar rcs $@ $(OBJ)
	@echo "$(NAME) Created"

# Object Files Compilation Rule
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) $(IFLAG) -c $< -o $@

# Targets
all:	$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "OBJ Deleted"

fclean:		clean
	@rm -f $(NAME)
	@echo "$(NAME) Deleted"

re:	fclean all

# Phony Targets
.PHONY: all clean fclean re
