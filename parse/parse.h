#ifndef PARSE_H
# define PARSE_H

# include "../validation/validation.h"

typedef struct s_data
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_no;
    int number_of_times_each_philosopher_must_eat;
}   t_data;

t_data  *init(int ac, char **av);
t_data  *data_init(int ac, char **av, t_data *data);

#endif