/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:39:30 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/10/13 14:44:13 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (ac < 5 || ac > 6 || !parse_args(&data, ac, av))
		return (write(2, "Error: Invalid arguments.\n", 27), 1);
	data.start_time = get_time();
	data.stop = 0;
	if (!init_forks_and_philos(&data))
		return (1);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine,
			&data.philos[i]);
		i++;
	}
	usleep(2000);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.philos[i].thread, NULL);
	cleanup(&data);
	return (0);
}
