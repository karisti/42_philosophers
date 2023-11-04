/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:27:40 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/27 19:16:30 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define A_FORK_R 0
# define A_FORK_L 1
# define A_EAT 2
# define A_SLEEP 3
# define A_THINK 4
# define A_DIED 5
# define A_ALL_EATEN 6
# define A_END 7

typedef struct s_philo
{
	pthread_t		tid;
	int				id;
	int				lfork;
	int				rfork;
	int				eat_count;
	struct s_info	*info;
	long long		last_eat;
	int				limit;
	pthread_mutex_t	mutex;
	int				is_eating;
}					t_philo;

typedef struct s_info
{
	int				num_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	prints;
	int				end;
	t_philo			*philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_times_eat;
	int				p_done_eaten;
	long long		start_time;
}					t_info;

// main.c
int			exit_error(t_info *info, char *str, int clear);
void		clear_info(t_info *info);
void		print_info(t_info *info);

// init.c
int			init_info(t_info *info);
int			init_philos(t_info *info);
int			init_threads(t_info *info);

// utils.c
long long	get_time_now(void);
void		ft_sleep(long long time);
int			ft_strisnum(char *str);
int			ft_atoi(const char *str);

// actions.c & actions1.c
void		*do_actions(void *philo);
int			action_take_forks(t_philo *philo);
int			action_eat(t_philo *philo);
int			action_sleep(t_philo *philo);
void		*philo_alive(void *p);
void		print_action(t_philo *philo, int action_id);
#endif
