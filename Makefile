NAME=codexion
CC=cc
CFLAGS= -Wall -Wextra -Werror -pthread
CFILES= codexion.c coder_utils.c data.c dongle_utils.c validator.c
COBJ = $(CFILES:.c=.o)
CHEADERS= codexion.h

all: $(NAME)

$(NAME): $(COBJ)
	$(CC) $(CFLAGS) $(COBJ) -o $(NAME)

%.o: %.c $(CHEADERS)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(COBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
