# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 11:03:46 by josfelip          #+#    #+#              #
#    Updated: 2024/06/19 11:01:38 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
DEBUG_NAME = minishell_debug
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
HEADER_PATH = ./include/
HEADER_FILE = $(shell find $(HEADER_PATH) -name "*.h" | cut -d '/' -f3)
HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))
OBJ_PATH = ./obj/
DEBUG_OBJ_PATH = ./obj_debug/
SOURCES_PATH = ./src/
SOURCES = $(shell find $(SOURCES_PATH) -name "*.c" | cut -d '/' -f3)
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

$(NAME): $(OBJECTS) $(OBJ_PATH)main.o
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(OBJ_PATH)main.o -L $(LIB_PATH) -lft -lreadline
	@echo $(CYAN)" ----------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| MINISHELL executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------"$(COLOR_LIMITER)
	@echo " "

$(OBJ_PATH)%.o: $(SOURCES_PATH)%.c $(HEADER)
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) -c $(CFLAGS) $< -o $@ -I $(HEADER_PATH)
	@echo " "

$(OBJ_PATH)main.o: main.c $(HEADER)
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) -c $(CFLAGS) $< -o $@ -I $(HEADER_PATH)
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

rec: clean
	@make --no-print-directory

.PHONY: all clean fclean re libft debug rec
