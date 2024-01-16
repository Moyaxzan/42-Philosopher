/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:05:58 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/16 23:32:51 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	data->exit = false;
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
 	// gettimeofday(&philo->tv, NULL);
	// printf("us : %ld\n", philo->tv.tv_usec);
	// fflush(stdout);
	// usleep(20);
 	// gettimeofday(&philo->tv, NULL);
	// printf("us : %ld\n", philo->tv.tv_usec);
	exit_all(data, return_val);
	free(data);
	return (return_val);
}
