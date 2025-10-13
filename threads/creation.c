/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:38:11 by mohammad          #+#    #+#             */
/*   Updated: 2025/10/13 04:26:16 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include <string.h>

long long current_micros() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((long long)(tv.tv_sec) * 1000 + tv.tv_usec);
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

t_philosopher	*philo_creation(t_data *data, int i, pthread_mutex_t *l, pthread_mutex_t *r)
{
    t_philosopher *philo;

    philo = malloc(sizeof(t_philosopher));
    if (!philo)
        return (NULL);
    philo->id = i + 1;
    philo->philo_no = data->philo_no;
    philo->meals_eaten = 0;
	philo->died = 0;
	philo->last_meal_time = current_micros() + data->time_to_die;
    philo->time_to_die = data->time_to_die;
    philo->time_to_eat = data->time_to_eat;
    philo->time_to_sleep = data->time_to_sleep;
    philo->left = l;
    philo->right = r;
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

philo_t	**h(mutex_p *forks, philo_t **phil, t_data *data, void *(*f)(void*))
{
	int i;

	i = 0;
	while (i < data->philo_no)
	{
		phil[i] = philo_creation(data, i, &forks[(i + 1) % data->philo_no], &forks[i]);
		if (!phil[i])
			exit_free(i, phil, 1);
		if (pthread_create(&phil[i]->thread, NULL, f, phil[i]) != 0)
		{
			perror("Thread failed to be launched");
			exit_free(i, phil, 0);
		}
		i++;
	}
	return (phil);
}

t_philosopher    **philo_init(t_data *data, void *(*f)(void*))
{
    t_philosopher	**philosopher;
	pthread_mutex_t *forks;
    int		i;

	i = 0;
    forks = forks_creation(data->philo_no);
	if (!forks)
		return (NULL);
	philosopher = malloc(sizeof(t_philosopher *) * data->philo_no);
	if (!philosopher)
		return (NULL);
	philosopher = h(forks, philosopher, data, f);
	return (philosopher);
}
