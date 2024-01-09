/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/09 19:37:42 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# define PARSING_ERR 1
# include <unistd.h>
# include <stdio.h>

/*--------------parsing.c---------------*/
int		parsing(int argc, char *argv[]);

/*-----------parsing_utils.c------------*/
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);

/*----------------exit.c----------------*/
void	help(void);
int		parsing_error(char *arg, char *str);
int		errnl(char *str, int err_code);

#endif
