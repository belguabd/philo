# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 14:39:26 by belguabd          #+#    #+#              #
#    Updated: 2024/06/06 12:58:34 by belguabd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
CFLAGE = -Wall -Wextra -Werror #-fsanitize=address -g  #-fsanitize=thread -g
# ------folder------ #
UTILS = utils
SRC = src

# ------source------ #
SRC_M = main.c \
	$(SRC)/ft_free.c $(SRC)/philo_actions.c $(SRC)/philo_monitor.c $(SRC)/philo_routine.c $(SRC)/init_utils.c\
	$(UTILS)/ft_atoi.c $(UTILS)/ft_putendl_fd.c $(UTILS)/ft_strlen.c \
	$(UTILS)/ft_parsing.c \

#------object------#
OBJ = $(SRC_M:.c=.o)

#------all------#
all: $(NAME)

#------compilation------#
$(NAME): $(OBJ)
	$(CC) $(CFLAGE) $(OBJ) -o $(NAME) 

#------object------#
%.o : %.c include/philo.h
	$(CC) $(CFLAGE) -c $< -o $@

#------clean------#
clean:
	rm -f $(OBJ)

#------fclean------#
fclean: clean
	rm -f $(NAME)

#------re------#
re: fclean all