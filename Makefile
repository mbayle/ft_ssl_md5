# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmontagn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/18 04:08:14 by lmontagn          #+#    #+#              #
#    Updated: 2020/03/06 03:52:34 by lmontagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

COMPILER = clang
FLAGS = -Wall -Wextra -Werror
OFLAGS = -c -I includes

SRCS_PATH		= srcs
OBJS_PATH		= objs

SRCS	=	main.c \
			hash.c \
			misc.c

OBJS		= $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS))

INCLUDES =	includes

all : $(NAME)

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(COMPILER) $(FLAGS) $(OFLAGS) -o $@ $<

$(NAME) : $(OBJS)
	@echo -e "Objects creation for $(NAME)...\t\t[ DONE ]"
	@/bin/echo -n "Compiling $(NAME) binary..."
	@$(COMPILER) -o $(NAME) $(OBJS)
	@echo -e "\t\t[ DONE ]"
	@echo -e "\n'$(NAME)' binary executable successfully created.\n"

clean :
	@rm -rf $(OBJS)
	@echo "Object files removed"

fclean : clean
	@rm -f $(NAME)
	@echo "Binary files removed."

re : fclean all

.PHONY : fclean re clean all

