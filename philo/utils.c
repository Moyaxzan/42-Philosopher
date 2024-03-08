/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:16:44 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/08 14:06:26 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_msg2(t_data *data, int num, t_state state, long int time)
{
	if (state == E_EAT)
		printf("%ld %d is eating\n", time - data->start_time, num);
	else if (state == E_THINK)
		printf("%ld %d is thinking\n", time - data->start_time, num);
	else
		printf("%ld %d died\n", time - data->start_time, num);
}

long int	print_msg(t_data *data, int num, t_state state)
{
	long int	time;

	time = get_time_ms();
	if (stop(data) && state != E_DIE)
		return (1);
	pthread_mutex_lock(&data->write_lock);
	if (state == E_SLEEP)
		printf("%ld %d is sleeping\n", time - data->start_time, num);
	else if (state == E_FORK)
		printf("%ld %d has taken a fork\n", time - data->start_time, num);
	else
		print_msg2(data, num, state, time);
	pthread_mutex_unlock(&data->write_lock);
	return (time);
}

time_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
