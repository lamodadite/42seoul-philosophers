#include "philosophers.h"

int	eat_delicious_spagetti(t_philo *philo)
{
	pthread_mutex_lock(&(philo->l_fork->m_fork));
	if (philo_says(philo, TAKE_FORK_MSG) == 1)
		return (1);
	philo->l_fork->fork_state = 1;
	pthread_mutex_lock(&(philo->r_fork->m_fork));
	if (philo_says(philo, TAKE_FORK_MSG) == 1)
		return (1);
	philo->r_fork->fork_state = 1;
	//printf("philo[%d]'s time_to_die(die_time = %d) -> %lld\n", philo->id, philo->info->die_time, philo->time_to_die);
	philo->time_to_die = timestamp() + philo->info->die_time;
	//printf("philo[%d]'s time_to_die(die_time = %d) -> %lld\n", philo->id, philo->info->die_time, philo->time_to_die);
	if (philo_says(philo, EAT_MSG) == 1)
		return (1);
	ft_usleep(philo->info->eat_time);
	philo->eat_num++;
	pthread_mutex_unlock(&(philo->l_fork->m_fork));
	philo->l_fork->fork_state = 0;
	pthread_mutex_unlock(&(philo->r_fork->m_fork));
	philo->r_fork->fork_state = 0;
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->time_to_die = timestamp() + philo->info->die_time;
	if (philo->id % 2 == 0)
	{
		if (philo_says(philo, THINK_MSG) == 1)
			return (NULL);
		ft_usleep(philo->info->eat_time / 2);
	}
	int	i =0;
	while (1)
	{
		if (eat_delicious_spagetti(philo) == 1)
			return (NULL);
		if (philo_says(philo, SLEEP_MSG) == 1)
			return (NULL);
		ft_usleep(philo->info->sleep_time);
		//ft_usleep(100);
		if (philo_says(philo, THINK_MSG) == 1)
			return (NULL);
		i++;
	}
	return (NULL);
}

void	thread_run(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = timestamp();
	while (++i < info->total_num)
	{
		pthread_create(&info->philos[i].tid, NULL, routine, &info->philos[i]);
		//usleep(1);
	}
}

void	monitoring(t_info *info)
{
	int	i;

	i = 0;
	while (check_death(&info->philos[i]) == 0)
	{
		//printf("monitoring -> %d\n", i);
		i++;
		if (i == info->total_num)
			i = 0;
	}
}

void	wait_thread(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_num)
		pthread_join(info->philos[i].tid, NULL);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (init(&info, ac, av) == 1)
		return (1);
	thread_run(&info);
	usleep(100);
	monitoring(&info);
	wait_thread(&info);
	return (0);
}
