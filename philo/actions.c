/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:11:17 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/08 13:48:38 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

int	ft_think(t_data *data, t_philo *philo)
{
	long	ttthink;

	ttthink = 0;
	if (stop(data))
		return (1);
	print_msg(data, philo->index, E_THINK);
	if (data->num_of_philo % 2)
		ttthink = 2 * data->tteat - data->ttsleep - 1;
	if (ttthink < 0)
		ttthink = 0;
	usleep(ttthink * 1000);
	return (0);
}

int	ft_pickup_forks(t_data *data, t_philo *philo)
{
	if (stop(data))
		return (1);
	if (data->num_of_philo == 1)
	{
		if (!pthread_mutex_lock(philo->l_fork))
			print_msg(data, philo->index, E_FORK);
		while (!stop(data))
			usleep(5000);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	else if (philo->index % 2)
	{
		if (!pthread_mutex_lock(philo->r_fork))
			print_msg(data, philo->index, E_FORK);
		if (!pthread_mutex_lock(philo->l_fork))
			print_msg(data, philo->index, E_FORK);
	}
	else
	{
		if (!pthread_mutex_lock(philo->l_fork))
			print_msg(data, philo->index, E_FORK);
		if (!pthread_mutex_lock(philo->r_fork))
			print_msg(data, philo->index, E_FORK);
	}
	return (0);
}

int	ft_release_forks(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	return (0);
}

int	ft_eat(t_data *data, t_philo *philo)
{
	long int	eat_time;

	if (stop(data))
		return (1);
	if (ft_pickup_forks(data, philo))
		return (1);
	eat_time = print_msg(data, philo->index, E_EAT);
	pthread_mutex_lock(&philo->lock_lst_eat);
	philo->tlst_eat = eat_time;
	pthread_mutex_unlock(&philo->lock_lst_eat);
	usleep(data->tteat * 1000);
	ft_release_forks(philo);
	philo->nb_eat++;
	return (0);
}
