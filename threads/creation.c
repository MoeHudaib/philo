/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:38:11 by mohammad          #+#    #+#             */
/*   Updated: 2025/10/11 21:18:09 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include <string.h>

long long current_micros() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((long long)(tv.tv_sec) * 1000000 + tv.tv_usec);
}

void	*my_f()
{
	return (NULL);
}

pthread_mutex_t	*forks_creation(int philo_no)
{
	pthread_mutex_t	*forks;
	int	i;

	i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * philo_no);
	if (!forks)
		return (NULL);
	while (i < philo_no)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philosopher	*philo_creation(t_data *data, int i)
{
	t_philosopher *philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->philo_no = data->philo_no;
	philo->meals_eaten = 0;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	return (philo);
}

void	exit_free(int i, t_philosopher **philo, int flag)
{
	int	count;

	count = 0;
	while (count < i)
		free(philo[count++]);
	free(philo);
	if (flag)
		printf("Memory Allocation Failure.\n");
}

void    philo_init(t_data *data)
{
    t_philosopher	**philosopher;
    int		i;

	i = 0;
	philosopher = malloc(sizeof(t_philosopher *) * data->philo_no);
	while (i < data->philo_no)
	{
		philosopher[i] = philo_creation(data, i);
		if (!philosopher[i])
			exit_free(i, philosopher, 1);
		if (pthread_create(&philosopher[i]->thread, NULL, my_f, NULL) != 0)
		{
			perror("Thread failed to be launched");
			exit_free(i, philosopher, 0);
		}
		i++;
	}
	i = 0;
	while (i < data->philo_no)
	{
		pthread_join(philosopher[i]->thread, NULL);
		i++;
    }
}