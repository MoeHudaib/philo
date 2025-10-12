/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:34:54 by mohammad          #+#    #+#             */
/*   Updated: 2025/10/12 18:48:52 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "../parse/parse.h"
#include "../validation/validation.h"

typedef struct s_philosopher
{
    int             id;
    int             philo_no;
    long             last_meal_time;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             died;
    int             meals_eaten;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    pthread_t       thread;
}                   t_philosopher;

typedef pthread_mutex_t mutex_p;
typedef t_philosopher philo_t;

/*     routine     */
void	*detector(void *arg);
void            picking_status(int rtorlft, int tkorlv, int id);
void            eat(int id, int time_to_eat);
void            sleeping(int id, int time_to_sleep);
void            think(int id);
long long       current_micros();
t_philosopher    **philo_init(t_data *data, void *(*f)(void*));
pthread_mutex_t *forks_creation(int philo_no);
int   init_detective(t_philosopher **d, t_data *data);

#endif