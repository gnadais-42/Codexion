#include "codexion.h"

static int	is_schedule_valid(char *schedule);
static int	overflow(char *number, char sign);
static int	is_number_valid(char *number);
static void	skip_leading_zeros(char **number);

static int is_schedule_valid(char *schedule)
{
	return (strcmp(schedule, "fifo") == 0 || strcmp(schedule, "edf") == 0);
}

static void	skip_leading_zeros(char **number)
{
	if (!**number)
		return ;
	while (**number == '0')
		(*number)++;
	if (!**number)
		(*number)--;
	return ;
}

static int	overflow(char *number, char sign)
{
	int	len;

	skip_leading_zeros(&number);
	len = strlen(number);
	if (len > 10)
		return (1);
	else if (len == 10)
	{
		if (sign == '-' && strcmp(number, "2147483648") > 0)
			return (1);
		else if (sign == '+' && strcmp(number, "2147483647") > 0)
			return (1);
	}
	return (0);
}

static int	is_number_valid(char *number)
{
	char	sign;
	int	n;

	n = atoi(number);
	while (*number == ' ')
		number++;
	if (*number == '-' && *(number + 1))
	{
		number++;
		sign = '-';
	}
	else
	{
		if (*number == '+' && *(number + 1))
			number++;
		sign = '+';
	}
	if (overflow(number, sign))
		return (0);
	if (n < 1)
		return (0);
	return (1);
}

int validator(int argc, char *argv[])
{
	char	sign;

	if (argc != 9)
		return (0);
	for (int i = 1; i < 8; i++){
		if (!is_number_valid(argv[i]))
			return (0);
	}
	if (!is_schedule_valid(argv[8]))
		return (0);
	return (1);
}
/*
int main(int argc, char *argv[])
{
	if (validator(argc, argv))
		printf("Valid\n");
	else
		printf("Invalid\n");
}*/
