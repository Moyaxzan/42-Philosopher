/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:13:57 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/16 19:07:42 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (exit_all(data, FATAL_ERR));
	if (pthread_mutex_init(&data->forks[i], NULL))
		return (FATAL_ERR);
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (FATAL_ERR);
		i++;
	}
	return (0);
}
