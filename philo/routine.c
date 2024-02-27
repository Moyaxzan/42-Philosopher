/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/02/27 16:09:43 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	ft_eat(t_data *data, t_philo *philo)
{
	long int	eat_time;

	if (stop(data))
		return (1);
	eat_time = print_msg(data, philo->index, E_EAT);
	philo->state = E_EAT;
	usleep(data->tteat * 1000);
	pthread_mutex_lock(&philo->lock_lst_eat);
	philo->tlst_eat = eat_time;
	pthread_mutex_unlock(&philo->lock_lst_eat);
	philo->nb_eat++;
	// no need to lock if philo check his nb of eat
	return (0);
}

int	eatnsleep(t_data *data, t_philo *philo)
{
	if (!pthread_mutex_lock(philo->r_fork))
		print_msg(data, philo->index, E_FORK);
	if (!pthread_mutex_lock(philo->l_fork))
		print_msg(data, philo->index, E_FORK);
	if (ft_eat(data, philo))
		return (1);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	philo->state = E_SLEEP;
	usleep(data->ttsleep * 1000);
	return (0);
}

void	*routine(void *vphilo)
{
	t_philo			*philo;

	philo = vphilo;
	pthread_mutex_lock(&philo->data->start_lock);
	pthread_mutex_unlock(&philo->data->start_lock);
	philo->tlst_eat = philo->data->start_time;
	if (!(philo->index % 2))
		eatnsleep(philo->data, philo);
	else
	{
		usleep(philo->data->tteat * 1000);
		print_msg(philo->data, philo->index, E_DIE);
		eatnsleep(philo->data, philo);
	}
	// while (!stop(philo->data))
	// {
	//
	// }
	return (NULL);
}
