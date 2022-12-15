NAME = ft_ssl

COMPILER = clang 
FLAGS = -Wall -Wextra -Werror -g3 -ggdb3
OFLAGS = -c  -I includes

SRCS_PATH				= srcs
SRCS_MD5_PATH			= srcs/md5
SRCS_SHA256_PATH		= srcs/sha256
SRCS_SHA512_PATH		= srcs/sha512
SRCS_WHIRLPOOL_PATH		= srcs/whirlpool
OBJS_PATH				= objs

SRCS				=	main.c \
						utils.c \
						routing.c \
						endianness.c \
						display.c

SRCS_MD5			=	md5.c \
						utils_md5.c \
						operation.c

SRCS_SHA256			=	operations.c \
						sha256.c

SRCS_SHA512			=	sha512.c

SRCS_WHIRLPOOL		=	whirlpool.c \
						whirlpool_sbox.c 
					

OBJS		= $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS))
OBJS		+= $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS_MD5))
OBJS		+= $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS_SHA256))
OBJS		+= $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS_SHA512))
OBJS		+= $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS_WHIRLPOOL))

INCLUDES =	includes

all : $(NAME)

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(COMPILER) $(FLAGS) $(OFLAGS) -o $@ $<

$(OBJS_PATH)/%.o : $(SRCS_MD5_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(COMPILER) $(FLAGS) $(OFLAGS) -o $@ $<

$(OBJS_PATH)/%.o : $(SRCS_SHA256_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(COMPILER) $(FLAGS) $(OFLAGS) -o $@ $<

$(OBJS_PATH)/%.o : $(SRCS_SHA512_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(COMPILER) $(FLAGS) $(OFLAGS) -o $@ $<

$(OBJS_PATH)/%.o : $(SRCS_WHIRLPOOL_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(COMPILER) $(FLAGS) $(OFLAGS) -o $@ $<

$(NAME) :  $(OBJS_PATH) $(OBJS)
	@$(COMPILER) -lm -o $(NAME) $(OBJS)
	@echo "\033[0;32m[✓]\033[0m\033[0;32m [BUILD]\t\tft_ssl binary executable successfully created\033[0m"

clean :
	@rm -rf $(OBJS)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [MAKEFILE][CLEAN]   Deleted all objects\033[0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [MAKEFILE][FCLEAN]  Binary files removed\033[0m"

re : fclean all

.PHONY : fclean re clean all