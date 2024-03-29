/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:51 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/31 13:44:44 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	exit_all(t_data *data, int err_code)
{
	if (!data)
		return (err_code);
	destroy_forks(data);
	if (data->philosophers)
		free(data->philosophers);
	data->philosophers = NULL;
	return (err_code);
}

void	help(void)
{
	write(2, "./philo should take the following arguments:\n", 46);
	write(2, "\t◦ number_of_philosophers: ", 29);
	write(2, "The number of philosophers/forks\n", 34);
	write(2, "\t◦ time_to_die (in ms): ", 26);
	write(2, "The time + 1 a philo can live without eating\n", 46);
	write(2, "\t◦ time_to_eat (in ms): ", 26);
	write(2, "The time it takes for a philo to eat.\n", 39);
	write(2, "\t\tDuring that time, ", 21);
	write(2, "they will need to hold two forks.\n", 35);
	write(2, "\t◦ time_to_sleep (in ms): ", 28);
	write(2, "The time a philo will spend sleeping.\n", 39);
	write(2, "\t◦ number_of_times_each_philosopher_must_eat ", 47);
	write(2, "(optional argument):\n", 22);
	write(2, "\t\tNumber of time philo will ", 29);
	write(2, "eat before stopping simulation. ", 32);
	write(2, "(unless one of them dies)\n", 27);
	write(2, "\t\tIf not specified, ", 20);
	write(2, "the simulation stops when a philo dies.\n", 41);
}

int	parsing_error(char *arg, char *str)
{
	write(2, "Parsing error: ", 15);
	while (arg && *arg)
		write(2, arg++, 1);
	if (arg)
		write(2, ": ", 2);
	while (str && *str)
		write(2, str++, 1);
	write(2, "\n\nsee ./philo --help (-h) for usage\n", 37);
	return (PARSING_ERR);
}

int	errnl(char *str, int err_code)
{
	while (str && *str)
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
	return (err_code);
}
