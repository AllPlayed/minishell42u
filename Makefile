# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:14:43 by ullorent          #+#    #+#              #
#    Updated: 2022/04/05 12:13:15 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CSRC =	src/minishell.c		\
		src/ms_aux.c		\
		src/ms_input.c		\
		src/ms_input2.c		\
		src/ms_free.c		\
		src/ms_allocate.c	\
		src/ms_input_cases.c\
		src/ms_utils.c		\
		src/ms_utils2.c		\
		src/ms_builtins.c	\
		src/ms_pipes.c		\
		src/ms_process.c	\
		src/ms_error.c

OSRC = $(CSRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
LDFLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/
CPPFLAGS= -I/Users/$(USER)/.brew/opt/readline/include
GCCCMD = gcc

LIBFT = libft/libft.all

all: $(NAME)

.c.o: $(CSRC)
	$(GCCCMD) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

$(NAME): $(OSRC)
	make -C libft
	make -C libft/ bonus
	mv libft/libft.a .
	$(GCCCMD) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) libft.a $^ -o $(NAME)

clean:
	rm -f $(OSRC)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re