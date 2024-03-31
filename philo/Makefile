# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 11:17:20 by jovicto2          #+#    #+#              #
#    Updated: 2024/02/14 11:17:23 by jovicto2         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

# Variables
NAME					:= philo

SOURCES_DIR				:= sources/
OBJECTS_DIR				:= objects/
HEADERS_DIR				:= includes/

MAKE					:= make
CC						:= cc
CFLAGS					:= -Wall -Wextra -Werror -Wunreachable-code -lpthread -Ofast -g3 -O3
MKDIR					:= mkdir -p
RM						:= rm -rf

# Sources
FILES					:= common manage_dinner philosophers set_table
SOURCES					:= $(addprefix $(SOURCES_DIR), $(addsuffix .c, $(FILES)))
OBJECTS					:= $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(FILES)))
HEADERS					:= -I $(HEADERS_DIR)

# Colors
RED   					:= \033[0;31m
GREEN  					:= \033[0;32m
RESET  		 			:= \033[0m

# Rules
.PHONY: all clean fclean re

all:
	@if [ ! -f $(NAME) ]; then \
		$(MAKE) -s $(NAME); \
		if [ -f $(NAME) ]; then \
    		printf "$(GREEN)Compiled $(NAME) successfully!$(RESET)\n"; \
    	else \
    		printf "$(RED)$(NAME) is not compiled yet!$(RESET)\n"; \
		fi \
    else \
    	printf "$(RED)$(NAME) is already compiled!$(RESET)\n"; \
    fi

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(INCLUDES)

clean:
	@if [ -d $(OBJECTS_DIR) ]; then \
		$(RM) $(OBJECTS_DIR); \
		printf "$(GREEN)Cleaned objects from $(NAME) successfully!$(RESET)\n"; \
	else \
		printf "$(RED)Objects from $(NAME) are already cleaned!$(RESET)\n"; \
	fi

fclean: clean
	@if [ -f $(NAME) ]; then \
		$(RM) $(NAME); \
		printf "$(GREEN)Removed $(NAME) file successfully!$(RESET)\n"; \
	else \
		printf "$(RED)File $(NAME) is already removed!$(RESET)\n"; \
	fi

re: fclean
	@$(MAKE) -s

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@$(MKDIR) $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)