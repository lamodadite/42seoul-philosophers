#include <philosophers.h>

int	check_death(t_philo *philo)
{
	//printf("cur time = %lld\n", timestamp());
	//printf("philo->time_to_die = %lld\n", philo->time_to_die);
	if (timestamp() >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->info->m_state);
		philo->info->state = 1;
		pthread_mutex_lock(&philo->info->print);
		printf(DIE_MSG, timestamp() - philo->info->start_time, philo->id);
		pthread_mutex_unlock(&philo->info->print);
		pthread_mutex_unlock(&philo->info->m_state);
		return (1);
	}
	if (philo->eat_num >= philo->info->max_eat)
	{
		pthread_mutex_lock(&philo->info->m_state);
		philo->info->state = 1;
		pthread_mutex_unlock(&philo->info->m_state);
		return (1);
	}
	return (0);
}

int	philo_says(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info->print);
	pthread_mutex_lock(&philo->info->m_state);
	if (philo->info->state == 1)
	{
		pthread_mutex_unlock(&philo->info->m_state);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->m_state);
	printf(msg, timestamp() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	ft_usleep(int time)
{
	long long l_time;

	l_time = (long long) time;
	usleep((useconds_t) l_time * 1000);
	return (0);
}

long long	timestamp(void)
{
	struct timeval te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000) + (te.tv_usec / 1000);
}

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
