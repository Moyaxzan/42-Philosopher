/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:13:57 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/04 16:48:20 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

t_philo	*init_philosophers(t_data *data)
{
	t_philo	*philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo) * (data->num_of_philo));
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->num_of_philo)
	{
		philosophers[i].tlst_eat = -1; 
		philosophers[i].full = false;
		philosophers[i].index = i + 1;
		philosophers[i].data = data;
		philosophers[i].nb_eat = 0;
		philosophers[i].state = E_INIT_STATE;
		philosophers[i].l_fork = data->forks[i];
		//TODO: protect when only one philo
		philosophers[i].r_fork = data->forks
			[(i - 1 + data->num_of_philo) % data->num_of_philo];
		// dprintf(2, "%d got fork %d and %ld\n", philosophers[i].index, i,(i - 1 + data->num_of_philo) % data->num_of_philo);
		// fflush(stderr);
		pthread_mutex_init(&philosophers->lock_lst_eat, NULL);
		pthread_mutex_init(&philosophers->lock_full, NULL);
		i++;
	}
	return (philosophers);
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	init_mutexes(data);
	data->philosophers = init_philosophers(data);
	if (!data->philosophers)
		return (exit_all(data, FATAL_ERR));
	pthread_mutex_lock(&data->start_lock);
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, &routine, (void *)&data->philosophers[i]))
			return (exit_all(data, FATAL_ERR));
		i++;
	}
	data->start_time = get_time_ms();
	pthread_mutex_unlock(&data->start_lock);
	return (0);
}
