/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:05:58 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/02/13 14:24:37 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	print_msg(t_data *data, int num, t_state state)
{
	long int	time;

	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_lock(&data->start_lock);
	time = get_time_ms() - data->start_time;
	pthread_mutex_unlock(&data->start_lock);
	if (state == E_SLEEP)
		printf("%ld %d is sleeping\n", time, num);
	if (state == E_FORK)
		printf("%ld %d has taken a fork\n", time, num);
	if (state == E_EAT)
		printf("%ld %d is eating\n", time, num);
	if (state == E_THINK)
		printf("%ld %d is thinking\n", time, num);
	if (state == E_DIE)
		printf("%ld %d died\n", time, num);
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

int	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	return (0);
}

t_data	*init_data(void)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_of_philo = 0;
	data->ttdie = 0;
	data->tteat = 0;
	data->ttsleep = 0;
	data->max_eat = 0;
	data->forks = NULL;
	data->stop = 0;
	data->forks = NULL;
	return (data);
}

int	main(int argc, char *argv[])
{
	int				return_val;
	t_data			*data;

	data = init_data();
	if (!data)
		return (FATAL_ERR);
	return_val = parsing(data, argc, argv);
	if (return_val)
		return (return_val);
	return_val = init(data);
	ft_join(data);
	exit_all(data, return_val);
	free(data);
	return (return_val);
}
