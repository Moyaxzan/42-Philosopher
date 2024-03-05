/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:16:44 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/05 23:20:06 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_msg2(t_data *data, int num, t_state state, long int time)
{
	if (state == E_EAT)
	{
		pthread_mutex_lock(&data->write_lock);
		printf("%ld %d is eating\n", time - data->start_time, num);
		pthread_mutex_unlock(&data->write_lock);
	}
	else if (state == E_THINK)
	{
		pthread_mutex_lock(&data->write_lock);
		printf("%ld %d is thinking\n", time - data->start_time, num);
		pthread_mutex_unlock(&data->write_lock);
	}
	else
	{
		pthread_mutex_lock(&data->write_lock);
		printf("%ld %d died\n", time - data->start_time, num);
		pthread_mutex_unlock(&data->write_lock);
	}
}

long int	print_msg(t_data *data, int num, t_state state)
{
	long int	time;

	if (stop(data) && state != E_DIE)
		return (1);
	time = get_time_ms();
	if (state == E_SLEEP)
	{
		pthread_mutex_lock(&data->write_lock);
		printf("%ld %d is sleeping\n", time - data->start_time, num);
		pthread_mutex_unlock(&data->write_lock);
	}
	else if (state == E_FORK)
	{
		pthread_mutex_lock(&data->write_lock);
		printf("%ld %d has taken a fork\n", time - data->start_time, num);
		pthread_mutex_unlock(&data->write_lock);
	}
	else
		print_msg2(data, num, state, time);
	return (time);
}

time_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
