#include "./threads/threads.h"
int volatile death = 0;
int	is_valid(int ac, char **av)
{
	int i;

	i = 1;
    if (ac > 6 || ac < 5)
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

    while (!death)
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

void	*detector(void *arg)
{
	t_moe	*ps = (t_moe *)arg;
    int     i;

    i = 0;
	while (1)
	{
        while (i < ps->data->philo_no)
        {
            if (current_micros() > (ps->philo[i]->last_meal_time - current_micros()))
            {
                death = 1;
                printf("philo %d has died out of starvation.\n", ps->philo[i]->id);
                break;
            }
            i = (i + 1) % ps->data->philo_no;
        }
        break;
	}
    return (NULL);
}

pthread_t   init_detective(t_moe *moe)
{
    pthread_t   detectives;
    int         i;

    i = 0;
    if (pthread_create(&detectives, NULL, detector, moe) != 0)
    {
        perror("Thread failed to be launched");
        return (0);
    }
    return (detectives);
}

int main(int ac, char **av)
{
    t_data  *data;
    t_philosopher **philo;
    t_moe         *moe;
    pthread_t     tez;

    moe = malloc(sizeof(t_moe));
    int     i = 0;

    if (!is_valid(ac, av))
        return (EXIT_FAILURE);
    data = init(ac, av);
    philo = philo_init(data, start);
    moe->data = data;
    moe->philo = philo;
    tez = init_detective(moe);
    while (i < data->philo_no)
	{
		pthread_join(philo[i]->thread, NULL);
		i++;
    }
    pthread_join(tez, NULL);
}