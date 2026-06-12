#include "../codexion.h"

static int	overflow(char *number, char sign);
static int	is_number_valid(char *number);
static int	is_all_digit(char *number);
static void	skip_leading_zeros(char **number);

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

static int	is_all_digit(char *number)
{
	if (*number == '-' || *number == '+')
		number++;
	if (!*number)
		return (0);
	while (*number)
	{
		if (*number < '0' || *number > '9')
			return (0);
		number++;
	}
	return (1);
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
	if (argc != 9)
		return (0);
	for (int i = 1; i < 8; i++){
		if (!is_all_digit(argv[i]))
			return (0);
		if (!is_number_valid(argv[i]))
			return (0);
	}
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
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
	if (is_all_digit(argv[1]))
		printf("%s is all digits", argv[1]);
	else
		printf("%s is not all digits", argv[1]);
}*/
