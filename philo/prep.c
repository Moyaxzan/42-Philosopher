/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:13:57 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/16 23:34:05 by tsaint-p         ###   ########.fr       */
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
		philosophers[i].r_fork = NULL;
		philosophers[i].l_fork = NULL;
		philosophers[i].state = E_INIT_STATE;
		i++;
	}
	return (philosophers);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	init(t_data *data)
{
	int	i;
	t_routinearg	*arg;
	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (exit_all(data, FATAL_ERR));
	data->philosophers = init_philosophers(data);
	if (!data->philosophers)
		return (exit_all(data, FATAL_ERR));
	arg = malloc(sizeof(t_routinearg) * data->num_of_philo);
	if (!arg)
		return (exit_all(data, FATAL_ERR));
	while (i < data->num_of_philo)
	{
		arg[i].data = data;
		arg[i].philo = &data->philosophers[i];
		arg[i].index = i;
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (exit_all(data, FATAL_ERR));
		if (pthread_create(&data->philosophers[i].thread, NULL, &routine, (void *)&arg[i]))
			return (exit_all(data, FATAL_ERR));
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
			return (exit_all(data, FATAL_ERR));
	}
	destroy_forks(data);
	return (0);
}
