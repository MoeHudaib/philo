#include "parse.h"
#include <string.h>
#include <stdlib.h>

t_data  *data_init(int ac, char **av, t_data *data)
{
	int	philo_no;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;

    philo_no = atoi(av[1]);
    time_to_die = atoi(av[2]);
    time_to_eat = atoi(av[3]);
    time_to_sleep = atoi(av[4]);
    data->philo_no = philo_no;
    data->time_to_die = time_to_die;
    data->time_to_eat = time_to_eat;
    data->time_to_sleep = time_to_sleep;
    return (data);
}

t_data  *init(int ac, char **av)
{
    t_data  *data;
    int		number_of_times_each_philosopher_must_eat;

    if (ac == 6)
        number_of_times_each_philosopher_must_eat = atoi(av[5]);
    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    data = data_init(ac, av, data);
    data->number_of_times_each_philosopher_must_eat =
        number_of_times_each_philosopher_must_eat;
    return (data);
}
