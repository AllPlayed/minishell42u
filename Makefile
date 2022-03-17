# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:14:43 by ullorent          #+#    #+#              #
#    Updated: 2022/03/17 14:28:55 by ullorent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CSRC =	src/minishell.c	\
		src/ms_aux.c	\
		src/ms_input.c	
OSRC = $(CSRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra
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