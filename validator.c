#include <stdlib.h>

static int is_positive(int n){
	return (n > 0);
}

static int is_schedule_valid(char *schedule){
	return (schedule == "fifo" || schedule == "edf");
}

static int is_number(char *str){
	while (*str){
		if (*str < "0" || *str > "9")
			return (0);
	}
	return (1);
}

int validator(int argc, char *argv){
	if (argc != 9)
		return (0);
	for (int i = 1; i < 8; i++){
		if (!is_number(argv[i]) && !is_positive(atoi(argv[i])))
			return (0);
	}
	if (!is_schedule_valid(argv[8]))
		return (0);
	return (1);
}
