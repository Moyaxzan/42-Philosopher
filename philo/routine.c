/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/02/12 16:09:40 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

int	stop(t_data *data)
{
	pthread_mutex_unlock(&data->stop_lock);
	if (data->stop)
	{
		pthread_mutex_lock(&data->stop_lock);
		return (1);
	}
	pthread_mutex_lock(&data->stop_lock);
	return (0);
}

int	eatnsleep(t_philo *philo)
{
	
}

void	*routine(void *vphilo)
{
	t_philo			*philo;

	philo = vphilo;
	pthread_mutex_lock(&philo->data->start_lock);
	pthread_mutex_unlock(&philo->data->start_lock);
	philo->tlst_eat = philo->data->start_time;
	long time = get_time_ms();
	pthread_mutex_lock(&philo->data->write_lock);
	printf("philo %d: %ld\n", philo->index, time - philo->data->start_time);
	fflush(stdout);
	pthread_mutex_unlock(&philo->data->write_lock);
	while (!stop(philo->data))
	{

	}
	return (NULL);
}
