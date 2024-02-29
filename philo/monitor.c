/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:42:01 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/02/29 22:46:45 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_dead(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_lst_eat);
	if (get_time_ms() - philo->tlst_eat >= data->ttdie)
	{
		pthread_mutex_unlock(&philo->lock_lst_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock_lst_eat);
	return (0);
}


int	ft_monitor(t_data *data)
{
	int	stop;
	int	i;

	stop = 0;
	i = 0;
	while (!stop)
	{
		usleep(100);
		if (i == data->num_of_philo)
			i = 0;
		if (is_dead(data, &data->philosophers[i]))
		{
			print_msg(data, data->philosophers[i].index, E_DIE);
			stop = 1;
		}
		i++;
	}
	pthread_mutex_lock(&data->stop_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_lock);
	return (0);
}
