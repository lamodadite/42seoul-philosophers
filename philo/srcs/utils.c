#include <philosophers.h>

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

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
	return (result * sign);
}
