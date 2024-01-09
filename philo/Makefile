NAME = philo

#####	VARIABLES   #####
CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c exit.c parsing.c parsing_utils.c

OBJS = $(SRCS:.c=.o)

#####	RULES   #####
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
