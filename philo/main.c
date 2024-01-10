/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:05:58 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/10 01:24:15 by tsaint-p         ###   ########.fr       */
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
	return (data);
}

int	main(int argc, char *argv[])
{
	int		return_val;
	t_data	*data;

	data = init_data();
	if (!data)
		return (FATAL_ERR);
	return_val = parsing(data, argc, argv);
	return (return_val);
}
