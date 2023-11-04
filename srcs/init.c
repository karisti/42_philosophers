/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:37:19 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/27 19:17:06 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philos(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philos)
		return (0);
	i = -1;
	while (++i < info->num_philo)
	{
		info->philos[i].eat_count = 0;
		info->philos[i].id = i + 1;
		info->philos[i].last_eat = 0;
		info->philos[i].limit = info->t_die;
		info->philos[i].rfork = i;
		if (i + 1 < info->num_philo)
			info->philos[i].lfork = i + 1;
		else
			info->philos[i].lfork = 0;
		info->philos[i].info = info;
			info->philos[i].is_eating = 0;
		pthread_mutex_init(&info->philos[i].mutex, NULL);
	}
	return (1);
}

int	init_info(t_info *info)
{
	int	i;

	if (!init_philos(info))
		return (0);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->forks)
		return (0);
	info->end = 0;
	info->p_done_eaten = info->num_philo;
	pthread_mutex_init(&info->prints, NULL);
	i = 0;
	while (i < info->num_philo)
		pthread_mutex_init(&(info->forks[i++]), NULL);
	return (1);
}

int	init_threads(t_info *info)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	if (info->n_times_eat == 0)
	{
		print_action(info->philos, A_END);
		return (1);
	}
	i = 0;
	info->start_time = get_time_now();
	while (i < info->num_philo)
	{
		philo = (void *)(&info->philos[i]);
		if (pthread_create(&tid, NULL, do_actions, philo) != 0)
			return (0);
		info->philos[i].tid = tid;
		i++;
	}
	return (1);
}
