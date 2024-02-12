/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/02/12 22:22:20 by tsaint-p         ###   ########.fr       */
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

int	eatnsleep(t_data *data, t_philo *philo)
{
	long int	eat_time;

	if (!pthread_mutex_lock(philo->r_fork))
		print_msg(philo->index, E_FORK);
	if (!pthread_mutex_lock(philo->l_fork))
		print_msg(philo->index, E_FORK);
	eat_time = print_msg(philo->index, E_EAT);
	if (!stop(data))
	{
		philo->state = E_EAT;
		usleep(data->tteat * 1000);
		pthread_mutex_lock(&philo->lock_lst_eat);
		philo->tlst_eat = eat_time;
		pthread_mutex_unlock(&philo->lock_lst_eat);
		philo->nb_eat++;
	}
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
