# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#              #
#    Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME			=	skibidi_shell

# Compiler settings
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g3

# Directories
LIB_DIR			=	lib/
SRC_DIR			=	src/
OBJ_DIR			=	obj/
INC_DIR			=	include/

# Library paths
LIBFT_DIR		=	$(LIB_DIR)libft/

# Source files
SRC				=	skibidi_shell.c \
					$(wildcard $(SRC_DIR)*.c) #ATTENTION !! A ENLEVER

# Object files
OBJS			=	$(SRC:%.c=$(OBJ_DIR)%.o)

# Include and library flags
IFLAGS			=	$(addprefix -I, $(INC_DIR) $(LIBFT_DIR))
LFLAGS			=	$(addprefix -L, $(LIBFT_DIR))
LIBS			=	-lft

# Main target
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBS) -o $(NAME)
	@echo "Welcome $@ ! 🤩🤙"

# Object file compilation rule
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "Good Morning $(notdir $@) ! 👋😇"

# Targets
all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "See You Soon $(OBJ_DIR) And Your Content... 🤧💔"

fclean: clean
	@rm -f $(NAME)
	@echo "Bye-Bye $(NAME) ! 🥺💋"

re: fclean all

# Phony targets
.PHONY: all clean fclean re libft mlx
