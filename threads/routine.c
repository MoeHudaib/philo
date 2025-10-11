#include "threads.h"

void    think(int id)
{
    printf("%d is thinking.\n", id);
    usleep(1000);
}

void    sleeping(int id, int time_to_sleep)
{
    printf("%d is thinking.\n", id);
    usleep(time_to_sleep * 1000);
}

void    eat(int id, int time_to_eat)
{
    printf("%d is eating.\n", id);
    usleep(time_to_eat * 1000);
}

void    picking_status(int rtorlft, int tkorlv, int id)
{
    if (tkorlv)
    {
        if (rtorlft)
        {
            printf("%d takes right fork.\n", id);
        }
        else
        {
            printf("%d takes left fork.\n", id);
        }
    }
    else
    {
        if (rtorlft)
        {
            printf("%d returned right fork.\n", id);
        }
        else
        {
            printf("%d returned left fork.\n", id);
        }
    }
}

void	detector(void *arg)
{
	t_philosopher	*ps = (t_philosopher *)arg;
	int				i = 0;
	while (1)
	{
		if (ps[i].last_meal_time < current_micros())
		{
            printf("philo %d has died out of starvation.\n", ps->id);
			exit(EXIT_FAILURE);
		}
		i++;
		if (i >= 5)
			i = i % 5;
	}
}