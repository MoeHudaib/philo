# Simple flexible Makefile for a Philo project
CC := cc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -I ./includes
LIBS := ./libs/libft/libft.a

NAME := philo

# collect all .c files (searching up to subdirectories)
SRCS :=	./validation/input_validation.c \
		./threads/creation.c \
		./threads/routine.c \
		./parse/parse.c \
		./main.c

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	$(CC)  -g $(SRCS) $(LIBS) -o $@ $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all