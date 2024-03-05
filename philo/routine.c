/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/05 23:11:54 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_full(t_philo *philo)
{
	return (philo->data->max_eat != -1
		&& philo->nb_eat == philo->data->max_eat);
}

void	set_offset(t_data *data, t_philo *philo)
{
	if (philo->data->num_of_philo % 2)
	{
		if (philo->index == data->num_of_philo)
		{
			print_msg(data, philo->index, E_THINK);
			usleep((data->tteat - 1) * 1000 * 2);
		}
		else if (philo->index % 2)
		{
			print_msg(data, philo->index, E_THINK);
			usleep((data->tteat - 1) * 1000);
		}
	}
	else
	{
		if (philo->index % 2 == 0)
		{
			print_msg(data, philo->index, E_THINK);
			usleep((data->tteat - 1) * 1000);
		}
	}
}

void	*routine(void *vphilo)
{
	t_philo			*philo;

	philo = vphilo;
	pthread_mutex_lock(&philo->data->start_lock);
	pthread_mutex_unlock(&philo->data->start_lock);
	set_offset(philo->data, philo);
	while (!stop(philo->data))
	{
		if (ft_eat(philo->data, philo))
			break ;
		if (is_full(philo))
		{
			pthread_mutex_lock(&philo->lock_full);
			philo->full = true;
			pthread_mutex_unlock(&philo->lock_full);
		}
		if (!stop(philo->data))
		{
			print_msg(philo->data, philo->index, E_SLEEP);
			usleep(philo->data->ttsleep * 1000);
		}
		if (ft_think(philo->data, philo))
			break ;
	}
	return (NULL);
}
