# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 09:22:02 by belguabd          #+#    #+#              #
#    Updated: 2024/06/04 17:39:00 by belguabd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo_bonus
CFLAGE = -Wall -Wextra -Werror 

# ------folder------ #
UTILS = utils
SRC = src

# ------source------ #
SRC_B = main_bonus.c \
	$(UTILS)/ft_atoi_bonus.c $(UTILS)/ft_putendl_fd_bonus.c $(UTILS)/ft_strlen_bonus.c  \
	$(UTILS)/ft_parsing_bonus.c $(UTILS)/time_utils.c \
	$(SRC)/init_bonus.c $(SRC)/philo_actions_bonus.c $(SRC)/philo_routine.c

#------object------#
OBJ_B = $(SRC_B:.c=.o)

#------all------#
all: $(NAME)

#------compilation------#
$(NAME): $(OBJ_B)
	$(CC) $(CFLAGE) $(OBJ_B) -o $(NAME) 

#------object------#
%.o : %.c include/philo_bonus.h
	$(CC) $(CFLAGE) -c $< -o $@

#------clean------#
clean:
	rm -f $(OBJ_B)

#------fclean------#
fclean: clean
	rm -f $(NAME)

#------re------#
re: fclean all