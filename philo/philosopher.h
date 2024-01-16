/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/16 19:08:27 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# define PARSING_ERR 1
# define FATAL_ERR 4
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum e_state
{
	E_SLEEP = 10,
	E_EAT,
	E_THINK,
	E_DIE,
}	t_state;

typedef struct s_philo
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	mt_write;
	bool			exit;
	int				num_of_philo;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				max_eat;
	struct timeval	tv;
}	t_data;

/*--------------parsing.c---------------*/
int		parsing(t_data *data, int argc, char *argv[]);

/*-----------parsing_utils.c------------*/
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_atoi(const char *nptr);

/*----------------exit.c----------------*/
int		exit_all(t_data *data, int err_code);
void	help(void);
int		parsing_error(char *arg, char *str);
int		errnl(char *str, int err_code);

/*----------------prep.c----------------*/
int		init(t_data *data);

#endif
