/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:31:27 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/27 19:14:16 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_action(t_philo *philo, int action_id)
{
	long long	now;

	pthread_mutex_lock(&philo->info->prints);
	if (!philo->info->end)
	{
		now = get_time_now() - philo->info->start_time;
		if (action_id == A_FORK_R || action_id == A_FORK_L)
			printf("%llims %i has taken a fork\n",
				now, philo->id);
		else if (action_id == A_EAT)
			printf("%llims %i is eating\n", now, philo->id);
		else if (action_id == A_SLEEP)
			printf("%llims %i is sleeping\n", now, philo->id);
		else if (action_id == A_THINK)
			printf("%llims %i is thinking\n", now, philo->id);
		else if (action_id == A_DIED)
			printf("%llims %i died\n", now, philo->id);
		else if (action_id == A_END)
			printf("%llims all philos ended eating at least %i times\n",
				now, philo->info->n_times_eat);
		if (action_id == A_DIED || action_id == A_END)
			philo->info->end = 1;
	}
	pthread_mutex_unlock(&philo->info->prints);
}

long long	get_time_now(void)
{
	static struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_sleep(long long time)
{
	time = time + get_time_now();
	while (get_time_now() < time)
	{
		if (get_time_now() >= time)
			break ;
		usleep(50);
	}
}

int	ft_strisnum(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		num;
	int		signo;
	long	i;

	num = 0;
	signo = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signo = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * signo);
}
