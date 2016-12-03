# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/28 19:34:56 by mhurd             #+#    #+#              #
#    Updated: 2016/12/02 00:12:24 by mhurd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls

SRC		=	main.c \
			sort.c \
			handle_args.c

ifdef ALLOCWRAP
	LDFLAGS += $(HOME)/lib/alloc_wrap.c -ldl
endif
OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC		= gcc
# CFLAGS	= -Wall -Wextra -Werror -O3
CFLAGS = -Wall -Wextra

LIBFT	= ./libft/libft.a
LIBINC	= -I./libft
LIBLINK	= -L./libft -lft

PRINTF	= ./ft_printf/libftprintf.a
PFINC	= -I./ft_printf/includes
PFLINK	= -L./ft_printf -lftprintf

SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj libft printf $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(LIBINC) $(PFINC) -I $(INCDIR) -o $@ -c $<

libft: $(LIBFT)

printf: $(PRINTF)

$(LIBFT):
	make -C ./libft

$(PRINTF):
	make -C ./ft_printf

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ) $(LIBLINK) $(PFLINK)

clean:
	rm -rf $(OBJDIR)
	make -C ./libft clean
	make -C ./ft_printf clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean
	make -C ./ft_printf fclean

re: fclean all
