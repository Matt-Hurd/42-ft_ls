# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/25 19:00:08 by mhurd             #+#    #+#              #
#    Updated: 2016/12/01 23:58:28 by mhurd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a
FLAGS =	-Wall -Wextra -Werror
CC = 	gcc
ODIR =	bin/
IDIR =	includes/
SRC =
OBJ =	$(SRC:.c=.o)
EXT =	$(IDIR)ft_printf.h

EXT +=	Makefile
SRC = src/ft_printf.c \
	   src/helpers/flag_finder.c \
	   src/helpers/handle_padding.c \
	   src/helpers/handle_precision.c \
	   src/helpers/num_to_string.c \
	   src/helpers/wchar_to_str.c \
	   src/helpers/num_helpers.c \
	   src/conversions/ft_conv_s.c \
	   src/conversions/ft_conv_c.c \
	   src/conversions/ft_conv_nums.c \
	   src/conversions/ft_conv_unimp.c \
	   src/conversions/ft_conv_percent.c \
	   src/conversions/ft_conv_n.c \
	   libft/ft_memalloc.c \
	   libft/ft_putstr.c \
	   libft/ft_strchr.c \
	   libft/ft_strdup.c \
	   libft/ft_strncpy.c \
	   libft/ft_strnew.c \
	   libft/ft_bzero.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_strlen.c \
	   libft/ft_memset.c \
	   libft/ft_strcpy.c \
	   libft/ft_atoi.c \
	   libft/ft_isdigit.c \
	   libft/ft_isspace.c \
	   libft/ft_strnjoin.c \
	   libft/ft_memcpy.c \
	   libft/ft_itoa_base.c \
	   libft/ft_strjoin.c \
	   libft/ft_isalpha.c \
	   libft/ft_toupper.c \
	   libft/ft_isupper.c \
	   libft/ft_islower.c \
	   libft/ft_strcat.c \
	   libft/ft_strcmp.c \
	   libft/ft_isalnum.c \
	   libft/ft_isalpha.c \
	   libft/ft_strjoinf.c \
	   libft/ft_strcatf.c \
	   libft/ft_strequ.c

O =		$(addprefix $(ODIR), $(OBJ))

all: $(NAME)

love: all

norm:
	norminette $(S)

$(NAME): $(O) $(EXT)
	@ar rc $(NAME) $(O)
	@ranlib $(NAME)

$(ODIR)%.o: %.c $(EXT)
	@echo "-> Compiling $<..."
	@$(CC) $(FLAGS) -c -I includes $< -o $@

$(O): | ./bin

./bin:
	@mkdir $(ODIR)
	@mkdir $(ODIR)src/
	@mkdir $(ODIR)src/conversions/
	@mkdir $(ODIR)src/helpers/
	@mkdir $(ODIR)/libft/

test: $(NAME)
	$(CC) -o $@ -I includes main.c -L. -lftprintf

clean:
	@echo "-> Cleaning libft object files..."
	@rm -rf bin/
	@make -C libft/ clean

fclean: clean
	@echo "-> Cleaning $(NAME)..."
	@rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re norm
