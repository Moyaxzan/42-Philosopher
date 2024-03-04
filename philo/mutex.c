/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:47:49 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/04 14:56:02 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	if (!data->forks)
		return ;
	while (i < data->num_of_philo && data->forks[i])
	{
		pthread_mutex_destroy(data->forks[i]);
		free(data->forks[i]);
		data->forks[i] = NULL;
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

int	init_mutexes(t_data *data)
{
	int	i;

	if (!data)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t *) * data->num_of_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_of_philo)
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i] || pthread_mutex_init(data->forks[i], NULL))
		{
			data->forks[i] = NULL;
			return (destroy_forks(data), 1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (destroy_forks(data), 1);
	if (pthread_mutex_init(&data->start_lock, NULL))
		return (pthread_mutex_destroy(&data->write_lock),
			destroy_forks(data), 1);
	return (0);
}
