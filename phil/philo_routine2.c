/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:40:10 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/10/13 14:40:10 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo(t_data *data, int i, int *finished_eating)
{
	if (data->meals_required > 0)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			if (data->philos[i].meals_eaten < data->meals_required)
				finished_eating = 0;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			i++;
		}
		if (finished_eating)
		{
			set_stop(data);
			return ;
		}
	}
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	now;
	int		finished_eating;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		finished_eating = 1;
		now = get_time();
		check_philo(data, i, &finished_eating);
		i = 0;
		while (i < data->num_philos)
		{
			check_philo_death(data, i, now);
			if (check_stop(data))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
