/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:00:46 by karisti-          #+#    #+#             */
/*   Updated: 2022/03/01 17:15:55 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_params(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (0);
	while (argc-- > 1)
		if (!ft_strisnum(argv[argc]))
			return (0);
	return (1);
}

int	parse_params(t_info *info, int argc, char *argv[])
{
	if (!check_params(argc, argv))
		return (0);
	info->num_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_times_eat = -1;
	if (argc == 6)
		info->n_times_eat = ft_atoi(argv[5]);
	if (info->num_philo < 1 || info->t_die < 0
		|| info->t_eat < 0 || info->t_sleep < 0
		|| (argc == 6 && info->n_times_eat < 0))
		return (0);
	return (1);
}

int	exit_error(t_info *info, char *str, int clear)
{
	printf("Error: %s\n", str);
	if (clear)
		clear_info(info);
	return (1);
}

void	clear_info(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(info->prints));
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->philos[i].mutex);
		pthread_mutex_destroy(&(info->forks[i++]));
	}
	free(info->forks);
	free(info->philos);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	int		i;

	if (!parse_params(&info, argc, argv))
		return (exit_error(&info, "Wrong arguments", 0));
	if (!init_info(&info))
		return (exit_error(&info, "Error initiating", 0));
	if (!init_threads(&info))
		return (exit_error(&info, "Error in threads", 1));
	i = -1;
	while (++i < info.num_philo)
		pthread_join(info.philos[i].tid, 0);
	clear_info(&info);
	return (0);
}
