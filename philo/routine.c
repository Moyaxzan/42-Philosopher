/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/02/29 14:11:24 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <unistd.h>

int	stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->stop_lock);
	return (0);
}

int	ft_think(t_data *data, t_philo *philo)
{
	long	ttthink;

	print_msg(data, philo->index, E_THINK);
	if (data->num_of_philo % 2 == 0)
		return (0);
	ttthink = (data->tteat * 2) - data->ttsleep;
	if (ttthink < 0)
		ttthink = 0;
	usleep(ttthink * 0.42);
	return (0);
}

int	ft_eat(t_data *data, t_philo *philo)
{
	long int	eat_time;

	if (stop(data))
		return (1);
	if (!pthread_mutex_lock(philo->r_fork))
		print_msg(data, philo->index, E_FORK);
	if (!pthread_mutex_lock(philo->l_fork))
		print_msg(data, philo->index, E_FORK);
	eat_time = print_msg(data, philo->index, E_EAT);
	philo->state = E_EAT;
	usleep(data->tteat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&philo->lock_lst_eat);
	philo->tlst_eat = eat_time;
	pthread_mutex_unlock(&philo->lock_lst_eat);
	philo->nb_eat++;
	// no need to lock if philo check his nb of eat
	return (0);
}

int	is_full(t_philo *philo)
{
	return (philo->data->max_eat != -1
		&& philo->nb_eat == philo->data->max_eat);
}

void	set_offset(t_philo *philo)
{
	if (philo->data->num_of_philo % 2 == 0)
	{
		if (philo->index % 2 == 0)
			usleep(3e4);
	}
	else
	{
		if (philo->index % 2)
			ft_think(philo->data, philo);
	}
}

void	*routine(void *vphilo)
{
	t_philo			*philo;

	philo = vphilo;
	pthread_mutex_lock(&philo->data->start_lock);
	pthread_mutex_unlock(&philo->data->start_lock);
	philo->tlst_eat = philo->data->start_time;
	set_offset(philo);
	while (!stop(philo->data))
	{
		if (is_full(philo))
			break ;
		if (ft_eat(philo->data, philo))
			break ;
		print_msg(philo->data, philo->index, E_SLEEP);
		usleep(philo->data->ttsleep * 1000);
		ft_think(philo->data, philo);
	}
	return (NULL);
}
