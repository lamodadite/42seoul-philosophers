#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("[%d] running\n", philo->id);
	return (NULL);
}

void	thread_run(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_num)
	{
		pthread_create(&info->philos[i].tid, NULL, routine, &info->philos[i]);
	}
}

void	wait_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->info->total_num)
		pthread_join(philo[i].tid, NULL);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	t_info	info;

	if (init(&info, &philo, ac, av) == 1)
		return (1);
	thread_run(&info);
	wait_threads(&philo);
	return (0);
}
