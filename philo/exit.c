/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:51 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/09 18:57:37 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	help(void)
{
	write(2, "./philo should take the following arguments:\n", 45);
	write(2, "\t◦ number_of_philosophers: The number of philosophers/forks\n", 62);
	write(2, "\t◦ time_to_die (in ms): The time + 1 a philo can live without eating\n", 71);
	write(2, "\t◦ time_to_eat (in ms): The time it takes for a philo to eat.\n", 64);
	write(2, "\t\tDuring that time, they will need to hold two forks.\n", 54);
	write(2, "\t◦ time_to_sleep (in ms): The time a philo will spend sleeping.\n", 66);
	write(2, "\t◦ number_of_times_each_philosopher_must_eat (optional argument):\n", 69);
	write(2, "\t\tNumber of time philo will eat before stopping simulation. ", 60);
	write(2, "(unless one of them dies)\n", 26);
	write(2, "\t\tIf not specified, the simulation stops when a philo dies.\n", 60);
}

int	parsing_error(char *arg, char *str)
{
	write(2, "Parsing error: ", 15);
	while(arg && *arg)
		write(2, arg++, 1);
	if (arg)
		write(2, ": ", 2);
	while(str && *str)
		write(2, str++, 1);
	write(2, "\n\nsee ./philo --help (-h) for usage\n", 37);
	return (PARSING_ERR);
}

int	errnl(char *str, int err_code)
{
	while(str && *str)
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
	return (err_code);
}
