# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 13:16:39 by karisti-          #+#    #+#              #
#    Updated: 2022/03/01 17:25:54 by karisti-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project compilation files and directories

NAME	=	philo

CFILE	=	main.c \
			utils.c \
			init.c \
			actions.c \

SRCSFD	=	srcs/
OBJSFD	=	objs/
HDR_INC	=	-I./includes

SRCS	=	$(addprefix $(SRCSFD), $(CFILE))
OBJS	=	$(addprefix $(OBJSFD), $(CFILE:.c=.o))

# Compilation
COMP	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Colors
RED		= \033[0;31m
GREEN	= \033[0;32m
NONE	= \033[0m
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

all: project $(NAME)
	@echo "... project ready"

project:
	@echo "Checking project ..."

$(OBJSFD):
	@mkdir $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

$(OBJSFD)%.o: $(SRCSFD)%.c
	@$(COMP) $(CFLAGS) $(HDR_INC) -o $@ -c $<
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ object"

$(NAME): $(OBJSFD) $(OBJS) 
	@$(COMP) $(CFLAGS) $(OBJS) -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

clean:
	@echo "Cleaning project ..."
	@/bin/rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] Objects directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: project all clean fclean re test
