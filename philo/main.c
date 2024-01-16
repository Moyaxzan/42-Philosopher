/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:05:58 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/16 12:45:14 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*init_philo(void)
{
	t_philo	*philo;
	
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num_of_philo = 0;
	philo->ttdie = 0;
	philo->tteat = 0;
	philo->ttsleep = 0;
	philo->max_eat = 0;
	return (philo);
}

int	main(int argc, char *argv[])
{
	int				return_val;
	t_philo			*philo;

	philo = init_philo();
	if (!philo)
		return (FATAL_ERR);
	return_val = parsing(philo, argc, argv);
 	gettimeofday(&philo->tv, NULL);
	printf("us : %ld\n", philo->tv.tv_usec);
	fflush(stdout);
	usleep(20);
 	gettimeofday(&philo->tv, NULL);
	printf("us : %ld\n", philo->tv.tv_usec);
	return (return_val);
}
