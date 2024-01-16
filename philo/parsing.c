/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:07:30 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/16 12:35:42 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_numeric(char *arg)
{
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (0);
		arg++;
	}
	return (1);
}

int	is_int(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len > 11)
		return (0);
	if (len == 10 && ft_strcmp(arg, "2147483647") > 0)
		return (0);
	return (1);
}

int	fill_philo(t_philo *philo, char *arg, int i)
{
	int	val;

	val = ft_atoi(arg);
	if (!val)
		return (0);
	else if (i == 1)
		philo->num_of_philo = val;
	else if (i == 2)
		philo->ttdie = val;
	else if (i == 3)
		philo->tteat = val;
	else if (i == 4)
		philo->ttsleep = val;
	else if (i == 5)
		philo->max_eat = val;
	return (val);
}

int	parsing(t_philo *philo, int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc > 1 && (!ft_strcmp(argv[1], "-h")
			|| !ft_strcmp(argv[1], "--help")))
		return (help(), 1);
	if (argc != 5 && argc != 6)
		return (parsing_error(NULL, "wrong number of arguments."));
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
			return (parsing_error(argv[i], "not a numeric argument."));
		if (!is_int(argv[i]))
			return (parsing_error(argv[i], "greater than int"));
		if (!fill_philo(philo, argv[i], i))
			return (parsing_error(argv[i], "cannot be zero"));
		i++;
	}
	return (0);
}
