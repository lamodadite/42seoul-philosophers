#include <philosophers.h>

int	print_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	if (result > INT32_MAX || result < 0)
		return (-1);
	return (result * sign);
}
