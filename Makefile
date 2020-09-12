# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 18:51:58 by mabayle           #+#    #+#              #
#    Updated: 2020/04/29 10:20:25 by geargenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	ft_ssl

CC			:=	clang
LINKER		:=	clang -o 

DEBUG		:=	0

LIBFT		:=	libft/libft.a

INCLUDES	:=	./includes

INCS		=	./includes/get_next_line.h \

#libft
INCLUDES	:=	$(INCLUDES) -I$(dir $(LIBFT))includes
LDFLAGS		:=	-L$(dir $(LIBFT)) -lft

CFLAGS		:=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)
ifeq ($(DEBUG), 1)
	CFLAGS	:=	$(CFLAGS) -ggdb -fno-omit-frame-pointer
endif

SRC_PATH	:=	./src/
OBJ_PATH	:=	./obj/

SRC		:=	main.c \

OBJ		:=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))
SRC		:=	$(addprefix $(SRC_PATH), $(SRC))

all:
	@make $(NAME)

$(NAME):  $(LIBFT) $(OBJ)
	@$(LINKER) $(NAME) $(OBJ) $(LDFLAGS) -ltermcap
	@echo ""
	@echo "\033[0;32mft_ssl build done\033[0m"
	@echo ""

$(LIBFT):	$(dir $(LIBFT))Makefile
	@make -j4 -C $(dir $(LIBFT))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [ft_ssl] Compiling : \033[0m" $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [ft_ssl] Deleted all .o\033[0m"
	@rm -rf ft_ssl.dSYM

fclean:
	@make -j4 -C libft/ fclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [ft_ssl] Deleted all .o\033[0m"
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [ft_ssl] Deleted ft_ssl\033[0m"

re: fclean all

.PHONY:	all clean fclean re
