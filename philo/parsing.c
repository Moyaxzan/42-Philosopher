/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:07:30 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/09 18:33:48 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parsing(int argc, char *argv[])
{
	if (argc > 1 && (!ft_strcmp(argv[1], "-h") || !ft_strcmp(argv[1], "--help")))
		return (help(), 1);
	if (argc != 5 && argc != 6)
		parsing_error("wrong number of arguments.");
	(void)argv;
	return (0);
}
