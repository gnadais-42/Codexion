NAME=codexion
CC=cc
CFLAGS=-Wall -Werror -Wextra -pthread
CFILES= codexion.c \
		coders/coder.c coders/coder_utils.c \
		dongles/dongle.c \
		heap/heap.c heap/heap_utils.c heap/heap_insert.c heap/heap_peek.c heap/heap_pop.c heap/compare.c \
		routines/coder_routine.c routines/monitor_routine.c \
		sim/sim.c sim/sim_utils.c \
		utils/data.c utils/validator.c utils/time.c
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
