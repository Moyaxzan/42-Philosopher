/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:13:57 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/31 13:34:36 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		philosophers[i].r_fork = NULL;
		philosophers[i].l_fork = NULL;
		philosophers[i].state = E_INIT_STATE;
		philosophers[i].index = i;
		philosophers[i].data = data;
		i++;
	}
	return (philosophers);
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = init_philosophers(data);
	if (!data->philosophers)
		return (exit_all(data, FATAL_ERR));
	init_mutexes(data);
	pthread_mutex_lock(&data->start_lock);
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, &routine, (void *)&data->philosophers[i]))
			return (exit_all(data, FATAL_ERR));
		i++;
	}
	pthread_mutex_unlock(&data->start_lock);

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	destroy_forks(data);
	return (0);
}
