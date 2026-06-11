NAME=codexion
CC=cc
CFLAGS=-pthread
CFILES= codexion.c coder_utils.c data.c dongle_utils.c validator.c \
		heap.c heap_utils.c heap_pop.c simulation.c threads.c helpers.c \
		time.c routine.c coder.c dongle.c helpers_2.c actions.c
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
