/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:07:30 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/09 19:51:19 by tsaint-p         ###   ########.fr       */
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

int	parsing(int argc, char *argv[])
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
		i++;
	}
	return (0);
}
