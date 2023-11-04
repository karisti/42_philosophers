/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 20:11:40 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/27 19:37:37 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_alive(void *p)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)p;
	while (!philo->info->end)
	{
		if ((get_time_now() - philo->info->start_time > philo->limit
				&& !philo->is_eating) || (philo->info->n_times_eat > 0
				&& philo->info->p_done_eaten <= 0))
		{
			pthread_mutex_lock(&philo->mutex);
			if (philo->info->n_times_eat > 0 && philo->info->p_done_eaten <= 0)
				print_action(philo, A_END);
			else
				print_action(philo, A_DIED);
			i = 0;
			while (i < philo->info->num_philo)
			{
				pthread_mutex_unlock(&(philo->info->forks[i++]));
				pthread_mutex_unlock(&philo->mutex);
			}
			return ((void *) 1);
		}
	}
	return ((void *)0);
}

void	*do_actions(void *p)
{
	pthread_t	tid;
	t_philo		*philo;

	philo = (t_philo *)p;
	if (pthread_create(&tid, NULL, &philo_alive, philo) != 0)
		return ((void *) 1);
	while (!philo->info->end)
	{
		if (!action_take_forks(philo))
			return ((void *) 1);
		if (!action_eat(philo))
			return ((void *) 1);
		if (!action_sleep(philo))
			return ((void *) 1);
	}
	pthread_join(tid, 0);
	return ((void *)0);
}

int	action_take_forks(t_philo *philo)
{
	if (philo->info->end)
		return (0);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->info->forks[philo->rfork]);
		print_action(philo, A_FORK_R);
		if (philo->info->end)
			return (0);
		pthread_mutex_lock(&philo->info->forks[philo->lfork]);
		print_action(philo, A_FORK_L);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks[philo->lfork]);
		print_action(philo, A_FORK_L);
		if (philo->info->end)
			return (0);
		pthread_mutex_lock(&philo->info->forks[philo->rfork]);
		print_action(philo, A_FORK_R);
	}
	return (1);
}

int	action_eat(t_philo *philo)
{
	if (philo->info->end)
		return (0);
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time_now() - philo->info->start_time;
	philo->limit = philo->last_eat + philo->info->t_die;
	print_action(philo, A_EAT);
	ft_sleep(philo->info->t_eat);
	philo->eat_count++;
	if (philo->info->n_times_eat > 0
		&& philo->eat_count == philo->info->n_times_eat)
		philo->info->p_done_eaten--;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	return (1);
}

int	action_sleep(t_philo *philo)
{
	if (philo->info->end)
		return (0);
	print_action(philo, A_SLEEP);
	pthread_mutex_unlock(&philo->info->forks[philo->rfork]);
	pthread_mutex_unlock(&philo->info->forks[philo->lfork]);
	ft_sleep(philo->info->t_sleep);
	print_action(philo, A_THINK);
	return (1);
}
