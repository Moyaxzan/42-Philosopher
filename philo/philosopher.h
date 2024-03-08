/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/08 17:07:33 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# define PARSING_ERR 1
# define FATAL_ERR 4
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum e_state
{
	E_INIT_STATE = 0,
	E_SLEEP = 10,
	E_FORK,
	E_EAT,
	E_THINK,
	E_DIE,
}	t_state;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				index;
	int				nb_eat;
	bool			full;
	t_data			*data;
	long int		tlst_eat;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	lock_lst_eat;
	pthread_mutex_t	lock_full;
}	t_philo;

typedef struct s_data
{
	int				stop;
	long int		num_of_philo;
	long int		ttdie;
	long int		tteat;
	long int		ttsleep;
	long int		max_eat;
	long int		start_time;
	t_philo			*philosophers;
	pthread_mutex_t	**forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	start_lock;
	struct timeval	tv;
}	t_data;

/*---------------actions.c---------------*/
int			ft_eat(t_data *data, t_philo *philo);
int			ft_think(t_data *data, t_philo *philo);

/*----------------mutex.c----------------*/
void		destroy_forks(t_data *data);
int			init_mutexes(t_data *data);

/*---------------parsing.c---------------*/
int			parsing(t_data *data, int argc, char *argv[]);

/*------------parsing_utils.c------------*/
int			ft_strcmp(char *s1, char *s2);
int			ft_strlen(char *str);
int			ft_atoi(const char *nptr);

/*----------------exit.c-----------------*/
int			exit_all(t_data *data, int err_code);
void		help(void);
int			parsing_error(char *arg, char *str);
int			errnl(char *str, int err_code);

/*-----------------prep.c----------------*/
int			init(t_data *data);

/*---------------routine.c---------------*/
int			is_full(t_philo *philo);
void		*routine(void *vdata);

/*---------------monitor.c---------------*/
int			ft_monitor(t_data *data);
int			all_full(t_data *data);
int			stop(t_data *data);

/*-----------------utils.c---------------*/
time_t		get_time_ms(void);
long int	print_msg(t_data *data, int num, t_state state);
void		my_msleep(t_data *data, long int msec);

#endif
