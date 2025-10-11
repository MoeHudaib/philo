#include "./threads/threads.h"

int	is_valid(int ac, char **av)
{
	int i;

	i = 1;
    while (i < ac)
    {
        if (!valid(av[i]))
            exit(1);
        i++;
    }
	return (1);
}

int main(int ac, char **av)
{
    t_data  *data;

    if (!is_valid(ac, av))
        exit(EXIT_FAILURE);
    data = init(ac, av);
    printf("no of philos: %d\nt 2 die: %d\nt 2 eat: %d\nt 2 sleep: %d\n", data->philo_no, data->time_to_die, data->time_to_eat, data->time_to_sleep);
}
