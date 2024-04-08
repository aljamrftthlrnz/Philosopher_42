# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 11:15:07 by amirfatt          #+#    #+#              #
#    Updated: 2024/04/07 16:27:07 by amirfatt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
CC = cc
FLAGS= -pthread -Werror -Wall -Wextra -g 

FILES= main.c time.c utils.c error.c init.c threads.c philo_routine.c monitor.c

SRC_PATH= $(addprefix source/, $(FILES))

OBJECT= $(SRC_PATH:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME) $(FLAGS)
	@echo "<><><><><><><><><>Successfully created executable<><><><><><><><><>"

%.o: %.cc
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT)
	@echo "<><><><><><><><><><><><Object files deleted><><><><><><><><><><><>"

fclean: clean
	rm -f $(NAME)
	@echo "<><><><><><><><><><><><Executable deleted><><><><><><><><><><><>"

re: fclean all

.PHONY: all clean fclean debug
