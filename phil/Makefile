NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = main.c philo_utils.c philo_routine.c philo_init.c philo_routine2.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
