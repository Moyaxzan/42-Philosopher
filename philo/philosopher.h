/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/08 15:32:55 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <unistd.h>

/*--------------parsing.c---------------*/
int	parsing(int argc, char *argv[]);

/*----------------exit.c----------------*/
int	errnl(char *str, int err_code);

#endif
