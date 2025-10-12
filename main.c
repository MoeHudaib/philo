#include "./threads/threads.h"

int	is_valid(int ac, char **av)
{
	int i;

	i = 1;
    if (ac == 1 || ac > 6)
        return (0);
    while (i < ac)
    {
        if (!valid(av[i]))
            return (0);
        i++;
    }
	return (1);
}

void    lefting(t_philosopher  *philo)
{
    think(philo->id);
    pthread_mutex_lock(philo->left);
    picking_status(0, 1, philo->id);
    pthread_mutex_lock(philo->right);
    picking_status(1, 1, philo->id);
    eat(philo->id, philo->time_to_eat);
    philo->last_meal_time = current_micros() + philo->time_to_die;
    picking_status(1, 0, philo->id);
    pthread_mutex_unlock(philo->right);
    picking_status(0, 0, philo->id);
    pthread_mutex_unlock(philo->left);
    sleeping(philo->id, philo->time_to_sleep);
}

void    righting(t_philosopher  *philo)
{
    think(philo->id);
    pthread_mutex_lock(philo->right);
    picking_status(1, 1, philo->id);
    pthread_mutex_lock(philo->left);
    picking_status(0, 1, philo->id);
    eat(philo->id, philo->time_to_eat);
    philo->last_meal_time = current_micros() + philo->time_to_die;
    picking_status(0, 0, philo->id);
    pthread_mutex_unlock(philo->left);
    picking_status(1, 0, philo->id);
    pthread_mutex_unlock(philo->right);
    sleeping(philo->id, philo->time_to_sleep);
}

void    *start(void *arg)
{
    t_philosopher  *philo;
    int     i;

    philo = (t_philosopher *)arg;
    i = philo->id;

    while (!philo->died)
    {
        if (i % 2 == 0)
            righting(philo);
        else
            lefting(philo);
    }
    return (NULL);
}

void    continue_(t_philosopher **philo, pthread_mutex_t *forks, t_data *data)
{
    return ;
}

int   init_detective(t_philosopher **d, t_data *data)
{
    pthread_t   **detectives;
    int         i;

    i = 0;
    detectives = malloc(sizeof(pthread_t *) * data->philo_no);
    while (i < data->philo_no)
    {
        detectives[i] = malloc(sizeof(pthread_t));
        if (pthread_create(detectives[i], NULL, detector, d[i]) != 0)
        {
            perror("Thread failed to be launched");
            return (0);
        }
        i++;
    }
    i = 0;
	while (i < data->philo_no)
	{
		pthread_join(*detectives[i], NULL);
		i++;
    }
    return (1);
}

int main(int ac, char **av)
{
    t_data  *data;
    t_philosopher **philo;

    if (!is_valid(ac, av))
        return (EXIT_FAILURE);
    data = init(ac, av);
    philo = philo_init(data, start);
    init_detective(philo, data);
}
