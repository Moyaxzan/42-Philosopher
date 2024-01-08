/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:07:30 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/08 15:46:00 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parsing(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (1); //TODO error + help message
	(void)argv;
	return (0);
}
