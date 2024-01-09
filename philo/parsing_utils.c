/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:27:02 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/09 19:37:27 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
