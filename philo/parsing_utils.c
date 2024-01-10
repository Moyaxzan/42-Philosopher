/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:27:02 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/10 01:13:37 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	diff;

	diff = 0;
	i = 0;
	while (s2[i] != '\0' && s1[i] != '\0' && diff == 0)
	{
		diff = s1[i] - s2[i];
		i++;
	}
	if (diff == 0)
		diff = s1[i] - s2[i];
	return (diff);
}

static size_t	size_num(const char *nptr)
{
	int	i;

	i = 0;
	if (nptr != 0x0)
	{
		while (nptr[i] >= '0' && nptr[i] <= '9')
			i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	unsigned long		i;
	int					sign;
	int					nbr;
	unsigned long int	end_num;

	i = 0;
	sign = 1;
	nbr = 0;
	while (nptr[i] == 32 || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	end_num = i + size_num(&nptr[i]);
	while (i < end_num)
	{
		nbr = nbr * 10;
		nbr += (nptr[i] - '0');
		i++;
	}
	return (nbr * sign);
}
