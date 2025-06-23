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

# Project Name
NAME			=	skibidi_shell

# Compiler Setting
CC				=	gcc
CFLAG			=	-Wall -Wextra -Werror -g3

# Directory
LIB_DIR			=	lib/
SRC_DIR			=	src/
OBJ_DIR			=	obj/
INC_DIR			=	include/

# Library Path & File
LIBFT_DIR		=	$(LIB_DIR)libft/
LIBFT			=	$(LIBFT_DIR)libft.a
# Source File
SRC				=	$(shell find $(SRC_DIR) -name "*.c")
# Object File
OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Include Flag
IFLAG			=	$(addprefix -I, $(INC_DIR) $(LIBFT_DIR)/include)
# Library Flag
LFLAG			=	$(addprefix -L, $(LIBFT_DIR))

LIB				=	-lft -lreadline

# All Target
all: $(LIBFT) $(NAME)

# LibFT Make Rule
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

# Main Target
$(NAME): $(OBJ)
	@$(CC) $(CFLAG) $(OBJ) $(LFLAG) $(LIB) -o $(NAME)
	@echo "Welcome $@ ! 🤩🤙"

# Object File Compilation Rule
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) $(IFLAG) -c $< -o $@
	@echo "Good Morning $(notdir $@) ! 👋😇"

# Mandatory Target
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "See You Soon $(OBJ_DIR) And Your Content... 🤧💔"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "Bye-Bye $(NAME) ! 🥺💋"

re: fclean all

# Phony Target
.PHONY: all clean fclean re
