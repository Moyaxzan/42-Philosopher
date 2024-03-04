/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:42:01 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/04 16:56:29 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

int	is_dead(t_data *data, t_philo *philo)
{
	long	lst_eat;

	pthread_mutex_lock(&philo->lock_lst_eat);
	if (philo->tlst_eat == -1)
		lst_eat = data->start_time;
	else
		lst_eat = philo->tlst_eat;
	pthread_mutex_unlock(&philo->lock_lst_eat);
	// dprintf(2, "philo %d : %ld - %ld >= %ld \n", philo->index, get_time_ms(), lst_eat, data->ttdie);
	// fflush(stderr);
	if (get_time_ms() - lst_eat >= data->ttdie)
		return (1);
	return (0);
}

int	all_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philosophers[i].lock_full);
		if (data->philosophers[i].full == false)
		{
			pthread_mutex_unlock(&data->philosophers[i].lock_full);
			return (0);
		}
		pthread_mutex_unlock(&data->philosophers[i].lock_full);
		i++;
	}
	return (1);
}

int	ft_monitor(t_data *data)
{
	int	stop;
	int	i;

	stop = 0;
	i = 0;
	while (!stop && !all_full(data))
	{
		usleep(9000 / data->num_of_philo);
		if (i == data->num_of_philo)
			i = 0;
		if (is_dead(data, &data->philosophers[i]))
		{
			stop = 1;
			pthread_mutex_lock(&data->stop_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_lock);
			print_msg(data, data->philosophers[i].index, E_DIE);
		}
		i++;
	}
	// exit_all(data, 0);
	return (0);
}
