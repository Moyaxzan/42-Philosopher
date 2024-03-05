/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/05 12:34:48 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

	if (stop(data))
		return (1);
	print_msg(data, philo->index, E_THINK);
	if (data->num_of_philo % 2)
		ttthink = 2 * data->tteat - data->ttsleep;
	else
		ttthink = data->tteat - data->ttsleep;
	usleep(ttthink);
	return (0);
}

int	ft_pickup_forks(t_data *data, t_philo *philo)
{
	if (philo->index == data->num_of_philo)
	{
		if (!pthread_mutex_lock(philo->r_fork)) // 0x4AA7390
			print_msg(data, philo->index, E_FORK);
		if (!pthread_mutex_lock(philo->l_fork)) // 0x4AA7300
			print_msg(data, philo->index, E_FORK);
	}
	else
	{
		if (!pthread_mutex_lock(philo->l_fork)) // 0x4AA7300
			print_msg(data, philo->index, E_FORK);
		if (!pthread_mutex_lock(philo->r_fork)) // 0x4AA7390
			print_msg(data, philo->index, E_FORK);
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
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	// dprintf(2, "%d just ate at %ld\n", philo->index, philo->tlst_eat);
	// fflush(stderr);
	philo->nb_eat++;
	// no need to lock if philo check his nb of eat
	return (0);
}

int	is_full(t_philo *philo)
{
	return (philo->data->max_eat != -1
		&& philo->nb_eat == philo->data->max_eat);
}

void	set_offset(t_data *data, t_philo *philo)
{
	if (philo->data->num_of_philo % 2 == 0)
	{
		if (philo->index % 2 == 0)
			usleep((data->tteat - 1) * 1000);
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
			break ;
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
