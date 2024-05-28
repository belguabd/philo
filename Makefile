# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 14:39:26 by belguabd          #+#    #+#              #
#    Updated: 2024/05/28 12:00:07 by belguabd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
CFLAGE = -Wall -Wextra -Werror  -g #-pthread -fsanitize=thread #-fsanitize=address 

# ------folder------ #
UTILS = utils

# ------source------ #
SRC = main.c \
	$(UTILS)/ft_atoi.c $(UTILS)/ft_putendl_fd.c $(UTILS)/ft_strlen.c \
	$(UTILS)/ft_parsing.c

#------object------#
OBJ = $(SRC:.c=.o)

#------all------#
all: $(NAME)

#------compilation------#
$(NAME): $(OBJ)
	$(CC) $(CFLAGE) $(OBJ) -o $(NAME) 

#------object------#
%.o : %.c philo.h
	$(CC) $(CFLAGE) -c $< -o $@

#------clean------#
clean:
	rm -f $(OBJ)

#------fclean------#
fclean: clean
	rm -f $(NAME)

#------re------#
re: fclean all