/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:42:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/16 23:37:54 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *varg)
{
	t_routinearg	*arg;
	t_data			*data;
	// t_philo			*philo;

	arg = (t_routinearg *) varg;
	data = arg->data;
	// philo = arg->philo;
	pthread_mutex_lock(&data->mt_write);
	printf("philo %d: Hello world.\n", arg->index);
	pthread_mutex_unlock(&data->mt_write);
	return (varg);
}
