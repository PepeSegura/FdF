# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 16:12:27 by psegura-          #+#    #+#              #
#    Updated: 2024/03/09 13:23:14 by psegura-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

### Colors ###

#RESET	=	\033c
GREEN	=	\033[1;32m
RED		=	\033[0;31m
CYAN	=	\033[0;36m
WHITE	=	\033[0m

NAME = fdf

FDF_SRCS =						\
			main.c				\
			draw.c				\
			errors.c			\
			key_hook.c			\
			bresenham.c			\
			transformation.c	\
			set_screen_width.c	\
			read_and_store_map.c\
		
SRCS = $(addprefix srcs/, $(FDF_SRCS))

OBJS = $(SRCS:%.c=objs/%.o)
DEPS = $(OBJS:%.o=%.d)

LIB = libft/libft.a

CC = gcc

OS = $(shell uname -s)

CFLAGS	 = -Wall -Wextra -Werror -g3 -fsanitize=address#,leak
CFLAGS	+= -I inc
CFLAGS	+= -I libft
CFLAGS	+= -O3
CPPFLAGS = -MMD

ifeq ($(OS),Darwin)
	CFLAGS += -D OSX
	FLAGS_MLX =  -lmlx -framework OpenGL -framework AppKit 
endif
ifeq ($(OS),Linux)
	CFLAGS += -D LINUX
	CFLAGS += -fsanitize=leak -g3
	FLAGS_MLX =  -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
	FLAGS_MLX +=  -fsanitize=leak
	CFLAGS += -I/usr/include -Imlx_linux
endif

all: $(NAME)

$(NAME): objs $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(FLAGS_MLX) -o $(NAME)
	@echo "$(CYAN)FdF READY$(WHITE)"

objs:
	@mkdir -p objs/srcs/

objs/%.o: %.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -rf objs

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re:: fclean
re:: all

debug:: CFLAGS += -g3 -fsanitize=address#,leak
debug:: re

norma:
	@echo 6e6f726d696e65747465207372637320696e6320313e2f6465762f6e756c6c3b206966205b5b20243f202d65712030205d5d3b207468656e206e6f726d696e65747465207372637320696e633b20656c7365206e6f726d696e65747465207372637320696e63207c206772657020274572726f7227203b206669 | xxd -r -p | zsh

-include $(DEPS)

.PHONY: all clean fclean re norma debug
