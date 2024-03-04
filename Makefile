# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 11:03:46 by josfelip          #+#    #+#              #
#    Updated: 2024/02/26 16:53:46 by gfantoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
DEBUG_NAME = push_swap_debug
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g3

# Paths for libraries
LIB_PATH = ./lib
LIB_NAME = libft.a

# Colors Definition 
GREEN = "\033[32;1m"
RED = "\033[31;1m"
CYAN = "\033[36;1;3;208m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

# Paths definitions
HEADER_PATH = ./includes/
HEADER = $(HEADER_PATH)push_swap.h
OBJ_PATH = ./obj/
DEBUG_OBJ_PATH = ./obj_debug/
SOURCES_PATH = ./sources/
SOURCES = 	00_main.c 01_user_input_validation.c 02_indexing.c 03_do_moves.c \
			03_moves.c 04_pre_sort.c 05_target_position.c 06_comp_cost.c \
			07_cheapest_move.c 08_sort.c 09_push_swap.c 10_dial.c 93_utils.c \
			94_utils.c 95_utils.c 96_utils.c 97_utils.c 98_utils.c 99_2_utils.c \
			99_utils.c \
			bst_breadth.c bst_check_node.c bst_del_utils.c bst_min_max.c \
			bst_nodes.c bst_traversal.c
			
MANDATORY_SOURCES = $(addprefix $(SOURCES_PATH), $(SOURCES))

ifdef WITH_DEBUG
  NAME = $(DEBUG_NAME)
  CFLAGS = $(DFLAGS)
  OBJ_PATH = ./obj_debug/
endif

OBJECTS = $(addprefix $(OBJ_PATH), $(SOURCES:%.c=%.o))

all: libft $(OBJ_PATH) $(NAME)

libft:
	@make --directory=$(LIB_PATH) --no-print-directory

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L $(LIB_PATH) -lft
	@echo $(CYAN)" ----------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| PUSH_SWAP executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------"$(COLOR_LIMITER)
	@echo " "

$(OBJ_PATH)%.o: $(SOURCES_PATH)%.c $(HEADER)
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)
	@echo " "

clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	-rm -rf $(OBJ_PATH)
	-rm -rf $(DEBUG_OBJ_PATH)

fclean: clean
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@rm -rf $(NAME)
	@rm -rf $(DEBUG_NAME)
	@make fclean -C $(LIB_PATH) --no-print-directory

re: fclean
	@make --no-print-directory

.PHONY: all clean fclean re libft debug
